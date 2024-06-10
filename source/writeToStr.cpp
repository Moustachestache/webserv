
//  write src to dest. dont go over maxsize.
void    writeToStr(char *dest, const char *src, int srcSize)
{
    dest = new char[srcSize + 1]();
    int i = 0;
    while(i < srcSize)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}