import requests 
import json
import sys

# Lettura del input main.c
if len(sys.argv)>1:
    user_state = str(sys.argv[1])
    # print(state)

# Dataset, restituisce una Response contenente tutti i fligths, per leggerla come un JSON : dataset.json()
dataset = requests.get('https://opensky-network.org/api/states/all')

with open("data/data.json", mode="w") as outfile:
    json.dump(dataset.json(), outfile)

# Lettura del dataset e filtraggio dei voli
with open('data/data.json', mode='r') as infile:
    
    # Lettura del contenuto in una variabile
    dati = json.load(infile)

    # Nodo "states"
    states = dati["states"]
    
    # Informazione da salvare
    user_data = []

    for state in states:
        if(state[2]==user_state):
            user_data.append(state)

# Scrittura degli states filtrati
with open('data/data.txt', mode='w') as outfile:
    for state in user_data:  # user_data contiene solo stati filtrati
        # Scrivi solo i valori separati da spazio
        outfile.write(f"{state[5]} {state[6]} {state[7]}\n")


