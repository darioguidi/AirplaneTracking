import requests
import json
import sys
import math

if len(sys.argv) > 1:
    user_state = str(sys.argv[1])

dataset = requests.get('https://opensky-network.org/api/states/all')

with open("data/data.json", mode="w") as outfile:
    json.dump(dataset.json(), outfile)

# Funzione per trasformare lat/lon/alt in coordinate sferiche "unitarie"
def latlon_to_xyz(lat, lon, alt):
    if alt is None:
        alt = 0
    lat_rad = math.radians(lat)
    lon_rad = math.radians(lon)
    r = 1.0 + alt * 0.0001  # altitudine scalata, globo unitario
    scale = 200  # moltiplica la sfera per renderla visibile
    x = r * math.cos(lat_rad) * math.cos(lon_rad) * scale
    y = r * math.sin(lat_rad) * scale
    z = r * math.cos(lat_rad) * math.sin(lon_rad) * scale

    return x, y, z

with open('data/data.json', mode='r') as infile:
    dati = json.load(infile)
    states = dati["states"]
    user_data = []

    for state in states:
        if state[2] == user_state:
            lat = state[6]
            lon = state[5]
            alt = state[7]
            x, y, z = latlon_to_xyz(lat, lon, alt)
            user_data.append((x, y, z))

with open('data/data.txt', mode='w') as outfile:
    for x, y, z in user_data:
        outfile.write(f"{x},{y},{z}\n")

