# Airplane Tracking ✈️

Un'applicazione interattiva di tracciamento aereo in tempo reale che visualizza i dati dei voli globali su una sfera 3D. Il progetto integra Python per l'acquisizione dei dati e C con SDL2 per il rendering grafico.

## 🚀 Caratteristiche

- **Acquisizione Dati in Tempo Reale**: Recupera i dati dei voli live dall'API di OpenSky Network.
- **Visualizzazione 3D**: Renderizza un globo 3D semplificato utilizzando SDL2, proiettando le coordinate geografiche (latitudine, longitudine, altitudine) in uno spazio cartesiano 3D.
- **Navigazione Interattiva**: Permette di ruotare la visuale del globo in tempo reale utilizzando i tasti `W`, `A`, `S`, `D`.
- **Filtraggio per Paese**: Consente all'utente di selezionare un paese specifico per filtrare e visualizzare solo i voli associati a quello stato.
- **Aggiornamenti Automatici**: L'applicazione aggiorna automaticamente i dati dei voli ogni 5 secondi per garantire la precisione in tempo reale.

## 🛠️ Stack Tecnologico

- **Linguaggi**: C (logica core e rendering), Python 3 (acquisizione dati).
- **Libreria Grafica**: [SDL2](https://www.libsdl.org/) (Simple DirectMedia Layer).
- **API**: OpenSky Network REST API.
- **Build Tool**: GNU Make.

## 📋 Prerequisiti

Prima di eseguire il progetto, assicurarsi di avere installato:
- **Compilatore GCC**
- **Librerie di sviluppo SDL2** (es. `libsdl2-dev` su Ubuntu/Debian)
- **Python 3**
- **Libreria `requests` di Python**:
  ```bash
  pip install requests
  ```

## ⚙️ Setup e Configurazione

Lo script Python richiede l'autenticazione per accedere all'API di OpenSky Network. È necessario impostare le credenziali come variabili d'ambiente:

```bash
export OPEN_SKY_CLIENT_ID="tuo_client_id"
export OPEN_SKY_CLIENT_SECRET="tuo_client_secret"
```

## 🔨 Installazione ed Esecuzione

1. **Clonare il repository**
2. **Compilare il progetto** utilizzando il Makefile fornito:
   ```bash
   make
   ```
3. **Avviare l'applicazione**:
   ```bash
   ./airtracking
   ```

## 🕹️ Come Usare l'Applicazione

1. **Menu**: All'avvio, utilizzare il menu nel terminale per:
   - Selezionare un paese per visualizzare i suoi voli attivi.
   - Chiudere l'applicazione.
2. **Navigazione**: Una volta aperta la finestra di visualizzazione:
   - `W` / `S`: Ruotare il globo verticalmente.
   - `A` / `D`: Ruotare il globo orizzontalmente.
3. **Chiusura**: Chiudere la finestra SDL o utilizzare il menu per uscire.
