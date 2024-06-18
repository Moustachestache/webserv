#!/bin/bash

COOKIE_NAME="Error Guest" 
# Récupérer les arguments CGI
for ARG in "$@"; do
    case $ARG in
        GET_Cookie_name=*)
        COOKIE_NAME="${ARG#*=}"
        shift
        ;;
    esac
done

# Envoyer les en-têtes HTTP
echo "Content-type: text/html"
echo ""

# Afficher la page HTML
cat <<EOF
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Welcome Page</title>
</head>
<body>
    <h1>Hello, $COOKIE_NAME!</h1>
    <form method="POST" action="./rien.htm" enctype="multipart/form-data">
        <label for="picklename">Enter your name:</label>
        <input type="text" id="picklename" name="picklename">
        <button action="send">Submit</button>
    </form>
</body>
</html>
EOF
