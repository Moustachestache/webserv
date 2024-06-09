
//  write src to dest. dont go over maxsize.
void    writeToStr(char *dest, int destMaxSize, const char *src, int srcSize)
{
    int i = 0;
    for (dest = new char[destMaxSize]; i < destMaxSize && i < srcSize; i++)
    {
        dest[i] = src[i];
    }
    dest[i] = '\0';
}