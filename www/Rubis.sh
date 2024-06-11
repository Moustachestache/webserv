#!/bin/bash
#./Rubis.sh "description="lol"" "name=Toto"
# Fonction pour parser les arguments sous forme clé=valeur
parse_args() {
  for arg in "$@"
  do
    case $arg in
      name=*)
        NAME="${arg#*=}"
        shift
        ;;
      description=*)
        DESCRIPTION="${arg#*=}"
        shift
        ;;
      *)
        # On ignore les arguments non reconnus
        ;;
    esac
  done
}

# Lire les arguments de la requête (QUERY_STRING)
if [ -n "$QUERY_STRING" ]; then
  oldIFS=$IFS
  IFS='&'
  set -- $QUERY_STRING
  IFS=$oldIFS

  params=("$@")
else
  params=("$@")
fi

parse_args "${params[@]}"

# Début de la réponse HTTP
echo "Content-Type: text/html"
echo ""  # Ligne vide pour indiquer la fin des en-têtes HTTP

# Début du contenu HTML
echo "<html>"
echo "<head><title>CGI Script</title></head>"
echo "<body>"
echo "<h1>CGI Script en Shell de ${NAME:-Inconnue}</h1>"
echo "<p>${DESCRIPTION:-Pas de description}</p>"
echo "</body>"
echo "</html>"

