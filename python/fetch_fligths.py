import sys
from opensky_api import OpenSkyApi

api = OpenSkyApi()

print("Python executable in use:", sys.executable)
state = api.get_states()

print(state)