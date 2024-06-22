#!/bin/sh

# Initialiser les variables avec des valeurs par défaut
NAME="Inconnue"
DESCRIPTION="Pas de description"

# Fonction pour parser les arguments
parse_args() {
    for arg in "$@"; do
        case $arg in
            GET_name=*)
                NAME="${arg#*=}"
                ;;
            GET_description=*)
                DESCRIPTION="${arg#*=}"
                ;;
            *)
                #echo "Argument non reconnu: $arg"
                ;;
        esac
    done
}

# Appeler la fonction de parsing avec tous les arguments
parse_args "$@"

# Afficher les en-têtes HTTP
echo "Content-Type: text/html"
echo ""  # Ligne vide pour indiquer la fin des en-têtes HTTP

# Début du contenu HTML
echo "<html>"
echo "<head><title>CGI Script</title></head>"
echo "<body>"
echo "<h1>CGI Script en Shell de ${NAME}</h1>"
echo "<p>${DESCRIPTION}</p>"
echo "</body>"
echo "</html>"
