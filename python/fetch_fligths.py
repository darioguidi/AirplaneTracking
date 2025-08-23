import requests 
import time
import json

# Local Time (s)
local_time = time.localtime()
# print(local_time)

# Dataset, restituisce una Response, per leggerla come un JSON : dataset.json()
dataset = requests.get('https://opensky-network.org/api/states/all')

# Scrittura del dataset all'interno di un file JSON
with open('data/data.json', 'w') as outfile:
    # Scrittura dei dati
    json.dump(dataset.json(), outfile)


