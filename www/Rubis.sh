#!/bin/bash

# Envoyer l'en-tête de type de contenu
echo "Content-Type: text/html"
echo ""# Début du contenu HTML
echo "<html>"
echo "<head><title>CGI Script</title></head>"
echo "<body>"
echo "<h1>CGI Script en Shell</h1>"

# Afficher les variables d'environnement CGI
echo "<h2>Variables d'environnement CGI</h2>"
echo "<table border='1'>"
echo "<tr><th>Variable</th><th>Valeur</th></tr>"
for var in REQUEST_METHOD QUERY_STRING CONTENT_TYPE CONTENT_LENGTH; do
    echo "<tr><td>$var</td><td>${!var}</td></tr>"
done
echo "</table>"

# Afficher les paramètres de la requête GET
if [ "$REQUEST_METHOD" == "GET" ]; then
    echo "<h2>Paramètres de la requête GET</h2>"
    echo "<ul>"
    IFS='&' read -r -a params <<< "$QUERY_STRING"
    for param in "${params[@]}"; do
        echo "<li>$param</li>"
    done
    echo "</ul>"
fi # Fin du contenu HTML
echo "</body>"
echo "</html>"

