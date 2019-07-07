#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <Windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Shlwapi.lib")

#define STORE_FN "./stored"

BOOL load_settings(int* info)
{
    return SystemParametersInfo(SPI_GETMOUSE, 0, info, 0);
}

void store_settings(int* info)
{
    SystemParametersInfo(SPI_SETMOUSE, 0, info, 0);
}

int main(int argc, char** argv)
{
    int mouseinfo[3] = { 0, 0, 0 };
    FILE* fp;

    if (!PathFileExists(STORE_FN))
    {
        if (!load_settings(mouseinfo))
        {
            return 1;
        }
        
        if (!mouseinfo[0] && !mouseinfo[1] && !mouseinfo[2])
        {
            // force disable acceleration
            mouseinfo[0] = 6;
            mouseinfo[1] = 10;
            mouseinfo[2] = 1;
        }

        fp = fopen(STORE_FN, "wb");
        if (!fp)
        {
            return 1;
        }
        fwrite(mouseinfo, sizeof(int), 3, fp);
        fclose(fp);

        // clear acceleration profile
        mouseinfo[0] = 0;
        mouseinfo[1] = 0;
        mouseinfo[2] = 0;

        store_settings(mouseinfo);
        printf("acceleration disabled\n");
    }
    else
    {
        fp = fopen(STORE_FN, "rb");
        fread(mouseinfo, sizeof(int), 3, fp);
        fclose(fp);
        
        /*if (mouseinfo[2] == 0)
        {
            mouseinfo[2] = 1;
        }*/

        store_settings(mouseinfo);
        remove(STORE_FN);
        printf("acceleration enabled\n");
    }

    return 0;
}