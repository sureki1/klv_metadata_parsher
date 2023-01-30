#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <stdlib.h>

unsigned int a = 0;
int k = 0;
unsigned int data[188] = { 0, };
float slant_range;

void binary2hex_print(char* filename, char* buf, int len)
{
    int i = 0, j = 0;
    unsigned char* p1 = (unsigned char*)buf;
    unsigned char* p2 = (unsigned char*)buf;
    
    FILE* fp1 = NULL;

    fp1 = fopen("data.txt", "w");
   // printf("+++ %s (%s:%d)\n", "mainCodes", filename, len);
   // printf("----------------------------------------------------------------\n");
   // printf("++++++++++++++++ BINARY HEX +++++++++++++++++++ ++ ASCII +++++++\n");
   // printf("----------------------------------------------------------------\n");
    
    
    
    
    for (i = 0; i < len; i++)
    {
        //printf("%02x ", (unsigned int)*(p1 + i));

        //data[i%188] = (unsigned int)*(p1 + i);

        
        if ((unsigned int)*(p1 + i) == 0x47 && (unsigned int)*(p1 + i+1) == 0x40 && (unsigned int)*(p1 + i+2) == 0x42)
        {
            for (k = 0; k < 188; k++) {
                data[k] = (unsigned int)*(p1 + i + k);
                //printf("%02x", data[k]);
            }
           // printf("\n");
            
            
            //if (((i + 1) % 188 == 0) && (i > 0))
            {
                /*  for (j = 0; j < 188; j++)
                {
                   if (isprint(*(p2 + j)) && (iscntrl(*(p2 + j)) == 0))
                        printf("%c", *(p2 + j));
                    else
                        printf(".");
                }
                */

                // Metadata HEADER

                if ((data[0x46] == 0x06 && data[0x47] == 0x0E && data[0x48] == 0x2B && data[0x49] == 0x34 &&
                    data[0x4A] == 0x02 && data[0x4B] == 0x0B && data[0x4C] == 0x01 && data[0x4D] == 0x01 &&
                    data[0x4E] == 0x0e && data[0x4F] == 0x01 && data[0x50] == 0x03 && data[0x51] == 0x01 &&
                    data[0x52] == 0x01 && data[0x53] == 0x00 && data[0x54] == 0x00 && data[0x55] == 0x00) ||

                    (data[0x25] == 0x06 && data[0x26] == 0x0E && data[0x27] == 0x2B && data[0x28] == 0x34 &&
                    data[0x29] == 0x02 && data[0x2A] == 0x0B && data[0x2B] == 0x01 && data[0x2C] == 0x01)   )

                    //if (data[0x46] == 0x06 && data[0x47] == 0x0E )
                {

                    for (k = 0; k < 188; k++)
                    {
                      
                            fprintf(fp1, "%02x ", data[k]);
                          //  fprintf(fp1, "%02x", i);
                           // printf("%02x ", data[k]);
                           // printf("%02x ", i);

                        
                     

                    }


                    fprintf(fp1, "\n");



                    /*  slant range calculator : parsing 변경 필요

                        for (j = 132; j < 136; j++)
                        {
                            fprintf(fp1, "%02x ", data[j]);
                            printf("%02x ", data[j]);
                        }


                        a =data[132]<<24 | data[133]<<16 | data[134]<<8 | data[135];

                        slant_range = (float)a * 5000000 / 4294967295;

                        fprintf(fp1, "\t%f ",slant_range);
                        printf("\t%02f ", slant_range);



                        fprintf(fp1, "\n");
                        */
                }


                //printf("\n");
               // fprintf(fp1, "\n");
                p2 = p1 + i + 1;


            }
        }

    }

 /*   if ((((i + 1) % 16) <= 15) && ((i + 1) % 16 != 1))
    {

        for (j = (i + 1) % 16 - 1; j < 16; j++)
            printf("   ");

        for (j = 0; j < (i + 1) % 16 - 1; j++)
        {
            if (isprint(*(p2 + j)) && (iscntrl(*(p2 + j)) == 0))
                printf("%c", *(p2 + j));
            else
                printf(".");
        }
        printf("\n");
    } */
   // printf("\n----------------------------------------------- ----------------\n");

    fclose(fp1);

}


#define FILE_NAME "data.ts"

int main()
{
    FILE* fp = NULL;
    int size = 0;
    char* read_buf = NULL;

    fp = fopen(FILE_NAME, "rb"); //바이너리 읽기 모드
    if (fp == NULL)
    {
        printf("open error\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    read_buf = (char*)calloc(size + 1, sizeof(char));
    fread(read_buf, sizeof(char), size, fp);
   
    fclose(fp);
    //바이너리 파일 화면 출력
     //printf("%d\n", k);

    binary2hex_print((char*)FILE_NAME, read_buf, size);
        
    
    

    return 0;
}