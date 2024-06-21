#!/usr/bin/env python3
import sys
import os
import shutil

buffer = ""
answer = ""

if __name__ == "__main__":
    
    for line in sys.argv:
        # print("DEBUG" + line + "<br />")
        if line.find("FILE_file") > -1:
            pos = line.rfind(";")
            # print("     EUREKA!     >>>>>     " + line + "<br />")
            if pos > 0:
                buffer = line[pos + 1:]
                break

    if buffer == "":
        print("incorrect execution. Use form.<br/>")
        sys.exit()

    answer = "<meta http-equiv=\"refresh\" content=\"10s; URL=./index.html?upload=success\"\">"

    if os.path.exists(buffer) == False:
        answer += "cant find file<br/>"
    else:
        answer += "found file: " + buffer + "<br />"

    if shutil.copyfile(buffer, "www/42perpignan.free.fr/profile.gif"):
        os.remove(buffer)
        answer += "profile picture changed<br /><h1>redirecting ... in 10s</h1>"
    else:
        answer += "error changing profile pic<br />"

    print(answer)
