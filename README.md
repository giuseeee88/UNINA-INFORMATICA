# UNINA-INFORMATICA

Repository dedicata al Corso di Laurea in Informatica presso l'Università degli Studi di Napoli Federico II. Anno accademico di inizio 2024-2025

**NOTA**: Il materiale è relativo solamente al gruppo 1, se siete di altri gruppi è molto probabie che avrete professori diversi, vi conviene in quel caso usare materiale relativo a quello specifico professore. Potete trovare tutto il materiale necessario e tutti i gruppi telegram [quì](https://t.me/+7HOZaOMbgSphNGM0) se vi dovesse servire altro

**NOTA**: le cartelle indicate con completato sono praticamente gli esami che ho fatto quindi non per forza hanno contenuto dentro o contenuto completo, semplicemente è un mio remider per le cose che ho fatto

## Contenuti

Questa repository raccoglie materiale didattico, appunti, dispense e progetti relativi al percorso universitario.

### Struttura attuale:
- **Primo Anno**: Materiale relativo ai corsi del primo anno.
- **Secondo Anno**: Materiale relativo ai corsi del secondo anno.
- **Terzo Anno**: Coming Soon, Stay tuned
- **Guida Triennale**: Informazioni generali sul corso di studi. [**ATTENZIONE NON SEMPRE AGGIORNATA PER MIGLIOR PRECISIONE ANDARE SUL SITO E SCARICARE IL DOCUMENTO RELATIVO AL VOSTRO ANNO**](https://informatica.dieti.unina.it/index.php/it/laurea-triennale/guide-studenti-triennale)

## Obiettivo

L'obiettivo di questa repository è fungere da cloud pubblico per centralizzare tutte le risorse universitarie, facilitandone l'accesso e l'organizzazione nel tempo e la fruizione del materiale didattico. La repository verrà aggiornata costantemente con l'avanzare del percorso accademico.

## Come usare e aggiornare questa repository

Se vuoi avere tutto il materiale sul tuo computer e tenerlo sempre aggiornato con le ultime modifiche, segui questi semplici passaggi. Non preoccuparti se non hai mai usato Git o GitHub!

### 1. Installazione (Solo la prima volta)

Per scaricare e aggiornare automaticamente la cartella, devi installare un piccolo programma chiamato **Git**.  

- **Windows**:
  - **Metodo veloce (Terminale/PowerShell)**: Scrivi winget install -e --id Git.Git
  - **Metodo classico**: Scarica l'installer da [git-scm.com](https://git-scm.com/download/win).
- **macOS**:
  - **Metodo veloce (Homebrew)**: Scrivi rew install git
  - **Metodo classico**: Apri il Terminale, scrivi git --version e segui le istruzioni per installare i "Command Line Tools".
- **Linux**:
  - Ubuntu/Debian: sudo apt install git
  - Fedora: sudo dnf install git
  - Arch Linux: sudo pacman -S git

> **Nota per file grandi**: Questa repository utilizza **Git LFS** per gestire PDF e dispense pesanti. Dopo aver installato Git, scrivi nel terminale: git lfs install per assicurarti di scaricare correttamente tutti i file.

### 2. Scaricare la repository sul tuo PC (Clone)

Una volta installato Git, scegli una cartella sul tuo computer dove vuoi salvare il materiale (es. Documenti).  

1. Apri il terminale (su Windows si chiama **Git Bash** o **PowerShell**).
2. Scrivi il seguente comando e premi Invio:
   `ash
   git clone https://github.com/Carloj005/UNINA-INFORMATICA.git
   `
3. Ora avrai una cartella chiamata UNINA-INFORMATICA con tutto il contenuto.

### 3. Aggiornare periodicamente il materiale (Pull)

Quando vengono aggiunti nuovi appunti o modifiche su GitHub, basta aggiornare la cartella che hai già senza riscaricare tutto:

1. Apri il terminale dentro la cartella UNINA-INFORMATICA.
2. Scrivi questi comandi:
   `ash
   git fetch origin
   git pull
   `
3. Git scaricherà solo i file nuovi o modificati. Consigliamo di farlo ogni volta che vuoi studiare!
