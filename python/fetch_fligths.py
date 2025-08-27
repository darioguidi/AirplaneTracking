import requests
import json
import sys
import math
import os

# === 1. Recupera il paese richiesto ===
if len(sys.argv) > 1:
    user_state = str(sys.argv[1])
else:
    print("Uso: python fetch_fligths.py <Country>")
    sys.exit(1)

# === 2. Recupera credenziali dalle variabili d'ambiente ===
CLIENT_ID = os.getenv("OPEN_SKY_CLIENT_ID")
CLIENT_SECRET = os.getenv("OPEN_SKY_CLIENT_SECRET")

if not CLIENT_ID or not CLIENT_SECRET:
    print("Errore: devi impostare OPEN_SKY_CLIENT_ID e OPEN_SKY_CLIENT_SECRET come variabili d'ambiente")
    sys.exit(1)

# === 3. Richiedi token ===
auth_url = "https://auth.opensky-network.org/auth/realms/opensky-network/protocol/openid-connect/token"
data = {
    "grant_type": "client_credentials",
    "client_id": CLIENT_ID,
    "client_secret": CLIENT_SECRET,
}

resp = requests.post(auth_url, data=data)
if resp.status_code != 200:
    print("Errore ottenendo il token:", resp.text)
    sys.exit(1)

token = resp.json()["access_token"]

# === 4. Scarica dataset con header Authorization: Bearer ===
headers = {"Authorization": f"Bearer {token}"}
dataset = requests.get('https://opensky-network.org/api/states/all', headers=headers)

if dataset.status_code != 200:
    print("Errore API:", dataset.status_code, dataset.text)
    sys.exit(1)

# Debug
print("Filtro per stato:", user_state)

with open("data/data.json", mode="w") as outfile:
    json.dump(dataset.json(), outfile)

# === 5. Funzione coordinate ===
def latlon_to_xyz(lat, lon, alt):
    if alt is None:
        alt = 0
    lat_rad = math.radians(lat)
    lon_rad = math.radians(lon)
    r = 1.0 + alt * 0.0001  # altitudine scalata, globo unitario
    scale = 200
    x = r * math.cos(lat_rad) * math.cos(lon_rad) * scale
    y = r * math.sin(lat_rad) * scale
    z = r * math.cos(lat_rad) * math.sin(lon_rad) * scale
    return x, y, z

# === 6. Filtra e salva dati ===
with open('data/data.json', mode='r') as infile:
    dati = json.load(infile)

    if "states" not in dati:
        print("La risposta non contiene 'states':", dati)
        sys.exit(1)

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
