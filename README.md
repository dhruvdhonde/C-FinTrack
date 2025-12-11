# C-FinTrack


A minimal, console-based personal finance tracker written in plain C (single source file). Stores transactions in `transactions.csv` in the current directory.


## Features
- Add transactions (income or expense) with date, amount, category and note
- List all transactions
- Summary of total income, total expense, and balance
- Monthly summary filter (by `YYYY-MM`)
- Remove transaction by id
- Persistent storage in `transactions.csv` (CSV without header)


## File format (`transactions.csv`)
Each row is a CSV line:
