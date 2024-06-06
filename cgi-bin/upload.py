#   parse incoming data (post)
#   we assume we made the form and so we retreive the data
#   _postfiles is the array of uploaded files
#   struct in pstfiles is
#       //  name of the uploaded file
#       std::string fileName;
#       //  mime type as told by the browser
#       std::string mimeType;
#       //  file data
#       std::string rawData;

with open(fileName, "wb") as binary_file:
    # Write bytes to file
    binary_file.write(rawData)