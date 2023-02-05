import pynetpp_bindings
import gym
import numpy as np
from gym import spaces

class CustomEnv(gym.Env):
    def __init__(self) -> None:
        super(CustomEnv, self).__init__()

        self._interface = pynetpp_bindings.PynetppInterface("LoRaNetworkTest", "./model/omnetpp.ini", ["./model", "/opt/inet/src", "/opt/flora/src"], 10000, -12)
        self._env = self._interface.get_env()
        obs_space = self._env.get_observation_space()
        act_space = self._env.get_action_space()

        self._set_observation_space(obs_space)
        self._set_action_space(act_space)

        self._already_started = False

    def _set_observation_space(self, obs_space):
        if obs_space.get_space_type() == 'discrete':
            obs_space.__class__ = pynetpp_bindings.PynetppDiscreteSpace
            self.observation_space = spaces.Discrete(obs_space.get_n())
        elif obs_space.get_space_type().startswith('box'):
            obs_space.__class__ = pynetpp_bindings.PynetppBoxSpace
            #TODO: manage dtype
            
            self.observation_space = spaces.Box(obs_space.get_low(), obs_space.get_high(), obs_space.get_shape())

        else:
            raise ValueError(f"Observation space type not known: {obs_space.get_space_type()}")

    def _set_action_space(self, act_space):
        if act_space.get_space_type() == 'discrete':
            act_space.__class__ = pynetpp_bindings.PynetppDiscreteSpace
            self.action_space = spaces.Discrete(act_space.get_n())
        elif act_space.get_space_type().startswith('box'):
            act_space.__class__ = pynetpp_bindings.PynetppBoxSpace
            self.action_space = spaces.Box(act_space.get_low(), act_space.get_high(), act_space.get_shape())

        else:
            raise ValueError(f"Action space type not known: {act_space.get_space_type()}")

    def _get_observation(self):
        obs = self._env.get_observation()

        if isinstance(self.observation_space, spaces.Box):
            obs.__class__ = pynetpp_bindings.PynetppBoxContainerF
            return np.array(obs, copy=False)

        if isinstance(self.observation_space, spaces.Discrete):
            obs.__class__ = pynetpp_bindings.PynetppDiscreteContainer
            return obs.get_value()

    def reset(self):
        if (self._already_started):
            self._interface.reset()
        else:
            self._interface.startup()
            self._already_started = True

        self._env = self._interface.get_env()
        obs = self._get_observation()

        return obs

    def render(self):
        obs = self._get_observation()
        print(obs)

    def step(self, action):
        if isinstance(self.action_space, spaces.Discrete):
            act = pynetpp_bindings.PynetppDiscreteContainer(self.action_space.n)
            act.set_value(action)
        elif isinstance(self.action_space, spaces.Box):
            act = pynetpp_bindings.PynetppBoxContainerF.from_nparray(action)
        
        self._env.execute_action(act)

        try:
            self._interface.execute_step(20)
        except pynetpp_bindings.TimeLimitError:
            self._env.set_game_over(True)

        return self._get_observation(), self._env.get_reward(), self._env.get_game_over(), []

    def close(self):
        self._interface.stop()

# env = CustomEnv()
# obs = env.reset()
# # print(obs)

# # env.render()

# while True:
#     act = env.action_space.sample()
#     # act = 1
#     print(f"Taking action: {act}")

#     obs, reward, done, _ = env.step(act)
#     env.render()

#     if done:
#         break

# env.close()