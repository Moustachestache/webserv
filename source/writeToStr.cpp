
//  write src to dest. dont go over maxsize.
void    writeToStr(char *dest, int destMaxSize, const char *src, int srcSize)
{
    for (int i = 0; i < destMaxSize && i < srcSize; i++)
    {
        dest[i] = src[i];
    }
}
