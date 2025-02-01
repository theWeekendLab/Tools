# Regole per l'utilizzo di Git e GitHub

Queste regole servono a garantire un uso ordinato ed efficace di Git e GitHub nel nostro progetto.

---

# 1. Clonare il repository  
Per lavorare in locale, scaricare il repository con:

git clone https://github.com/theWeekendLab/Tools.git
cd nome-repo

# 1.1 Se hai già il repository, assicurati di essere aggiornato:
git pull origin main

Se hai modifiche locali non ancora salvate, usa lo stash:

git stash
git pull origin main
git stash pop


#2 Non lavorare direttamente su main, ma crea un branch per ogni modifica.(nel repository locale)
git checkout -b nome-branch

I nomi dei branch devono essere descrittivi:

    feature-nuovo-menu → Per nuove funzionalità
    fix-bug-login → Per risolvere bug
    refactor-codice → Per miglioramenti senza nuove funzionalità


#3 Dopo aver lavorato sul tuo branch:

git add nome-file
git commit -m "Descrizione chiara della modifica"
git push origin nome-branch

#4  autenticarti nel terminale per poter interagire con il tuo account GitHub.

gh auth login

#5 creare una Pull Request 

gh pr create --base main --head nome-branch --title "Titolo della PR" --body "Descrizione della PR"

--base main: Il branch di destinazione (di solito main).
--head nome-branch: Il tuo branch di origine (quello che hai creato e su cui hai fatto il push).
--title "Titolo della PR": Il titolo della tua Pull Request.
--body "Descrizione della PR": Una descrizione opzionale per spiegare le modifiche.

#6 merge e eliminazione branch remoto

gh pr merge nome-pr --merge
git checkout main  (aggiornamento branch locale)
git pull origin main
git push origin --delete nome-branch

