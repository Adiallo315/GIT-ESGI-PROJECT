import re

def lint_javascript(code):
    lines = code.split('\n')

    errors = []
    for i, line in enumerate(lines, start=1):
        # Nouvelle expression régulière pour détecter l'absence de point-virgule à la fin
        if not re.search(r';\s*$', line):
            errors.append(f"Ligne {i}: Pas de point-virgule à la fin de la ligne")

    return errors

with open("test_script.js", "r") as file:
    javascript_code = file.read()

linting_errors = lint_javascript(javascript_code)

if linting_errors:
    for error in linting_errors:
        print(f"Erreur de style : {error}")
else:
    print("Le code respecte les règles de style.")


