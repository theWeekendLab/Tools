# Regole per l'utilizzo di Git e GitHub

Queste regole servono a garantire un uso ordinato ed efficace di Git e GitHub nel nostro progetto. Seguire questa guida aiuterà a mantenere il codice pulito e a collaborare in modo efficiente con il team.

## 1. Clonare il repository

Per lavorare in locale, devi prima scaricare il repository dal server GitHub sul tuo computer.

```bash
git clone https://github.com/theWeekendLab/Tools.git
cd Tools  # Entra nella cartella del repository
```

Se hai già il repository, assicurati di essere aggiornato con le ultime modifiche:

```bash
git pull origin main
```

> **Nota:** Se hai modifiche locali non ancora salvate, usa lo stash per salvarle temporaneamente:

```bash
git stash  # Salva le modifiche senza committarle
git pull origin main  # Aggiorna il repository locale
git stash pop  # Ripristina le modifiche salvate
```

---

## 2. Creazione di un branch

Non lavorare direttamente sul branch `main`. Crea un nuovo branch per ogni modifica.

```bash
git checkout -b nome-branch
```

### Nomenclatura consigliata per i branch:
- **feature-nuovo-menu** → Per nuove funzionalità.
- **fix-bug-login** → Per risolvere bug.
- **refactor-codice** → Per miglioramenti senza nuove funzionalità.

> **Perché usare i branch?** Separare le modifiche permette di lavorare senza interferire con il codice stabile presente su `main`. Questo facilita anche la revisione del codice e la gestione delle modifiche.

---

## 3. Salvare e inviare le modifiche

Dopo aver lavorato sul tuo branch, devi salvare le modifiche e inviarle al repository remoto su GitHub.

### Passaggi:
1. **Aggiungere i file all'area di staging:**
   ```bash
   git add nome-file  # Oppure usa 'git add .' per aggiungere tutti i file modificati
   ```
   - Questo comando dice a Git quali file vuoi includere nel prossimo commit.

2. **Creare un commit:**
   ```bash
   git commit -m "Descrizione chiara della modifica"
   ```
   - Un commit è una sorta di "fotografia" del codice in un determinato stato. Ogni commit dovrebbe avere un messaggio chiaro che descriva i cambiamenti effettuati.

3. **Inviare il branch al repository remoto:**
   ```bash
   git push origin nome-branch
   ```
   - Questo comando carica il branch con le modifiche sul server GitHub.

---

## 4. Autenticazione con GitHub

Per interagire con GitHub dal terminale (es. creare Pull Request), devi autenticarti:

```bash
gh auth login
```

> **Nota:** L'autenticazione scade dopo 30 giorni e potrebbe essere necessario ripeterla.

---

## 5. Creare una Pull Request (PR)

Dopo aver inviato il branch su GitHub, devi creare una Pull Request per proporre l'integrazione delle modifiche nel branch `main`.

Puoi farlo tramite interfaccia grafica su GitHub oppure con il terminale:

```bash
gh pr create \
  --base main \
  --head nome-branch \
  --title "Titolo della PR" \
  --body "Descrizione della PR"
```

- `--base main`: Indica il branch di destinazione della PR (solitamente `main`).
- `--head nome-branch`: Indica il branch contenente le modifiche da unire.
- `--title "Titolo della PR"`: Fornisce un titolo chiaro alla PR.
- `--body "Descrizione della PR"`: Spiega le modifiche effettuate (opzionale ma consigliato).

---

## 6. Unire la Pull Request e eliminare il branch

Dopo la revisione e approvazione della Pull Request, puoi unirla e rimuovere il branch remoto.

1. **Unire la PR:**
   ```bash
   gh pr merge nome-pr --merge
   ```
   - Questo comando fonde le modifiche del branch con `main`.

2. **Tornare al branch `main` e aggiornare il repository locale:**
   ```bash
   git checkout main
   git pull origin main
   ```
   - Assicura che il repository locale sia aggiornato con le ultime modifiche dal repository remoto.

3. **Eliminare il branch remoto:**
   ```bash
   git push origin --delete nome-branch
   ```
   - Rimuove il branch remoto ormai inutile, evitando confusione e mantenendo il repository pulito.

---

Seguendo queste regole, il team potrà lavorare in modo organizzato, evitando conflitti e mantenendo il codice pulito e facilmente gestibile.


