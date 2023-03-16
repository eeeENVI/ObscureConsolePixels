#pragma once

#include "Color.h"

namespace op
{
    namespace Core
    {
        // wymaga optymalizacji pod zakres 0 - 255
        char* itoch(int value, char* result) 
        {	
                int base = 10;
                char* ptr = result, *ptr1 = result, tmp_char;
                int tmp_value;

                do {
                    tmp_value = value;
                    value /= base;
                    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
                } while ( value );

                
                *ptr-- = '\0';
                while(ptr1 < ptr) {
                    tmp_char = *ptr;
                    *ptr--= *ptr1;
                    *ptr1++ = tmp_char;
                }

                return result;
        }
          
        // wymaga optymalizacji ale i tak szybsze niz snprintf
        // formats buffor foreground AND background and returns counted chars (27 up to 39)
        int formatColorsOut(char* dst,Color fg,Color bg,char c)
        {

            const char* num1 = "\033[38;2;"; // 7 ( 0 - 6)
            const char* num2 = "\033[48;2;"; // 7 ( 7 - 13)
            int count = 21;

            char cfg[3][3];
            char bfg[3][3];

            itoch(fg.r,cfg[0]);
            itoch(fg.g,cfg[1]);
            itoch(fg.b,cfg[2]);
            
            itoch(bg.r,bfg[0]);
            itoch(bg.g,bfg[1]);
            itoch(bg.b,bfg[2]);
            
            for(int i = 0; i < 7; ++i)
            {
                *(dst++) =  num1[i];
            }
            
            for(int i = 0; i < 3; ++i)
            {
                for(int j = 0;j<3;++j)
                {
                    if(cfg[i][j] >= '0' && cfg[i][j] <= '9')
                    {
                        *(dst++) = cfg[i][j];
                        ++count;
                    }
                   
                }
                
                if(i<2) *(dst++) = ';'; 
            }

            *(dst++) = 'm';

            for(int i = 0; i < 7; ++i)
            {
                *(dst++) =  num2[i];
            }
            
            for(int i = 0; i < 3; ++i)
            {
                for(int j = 0;j<3;++j)
                {
                    if(bfg[i][j] >= '0' && bfg[i][j] <= '9')
                    {
                        *(dst++) = bfg[i][j];
                        ++count;
                    }
                    
                }
                
                if(i<2)*(dst++) = ';'; 
            }

            *(dst++) = 'm';
            *(dst++) = c;
            *(dst) = '\0';

            return count;
        }    

        // formats buffor foreground and returns counted chars (14 up to 20)
        int formatFgOut(char* dst,Color fg,char c)
        {
            const char* num1 = "\033[38;2;"; // 7 ( 0 - 6)
            int count = 11;
            char cfg[3][3];

            itoch(fg.r,cfg[0]);
            itoch(fg.g,cfg[1]);
            itoch(fg.b,cfg[2]);
            
            
            for(int i = 0; i < 7; ++i)
            {
                *(dst++) =  num1[i];
            }
            
            for(int i = 0; i < 3; ++i)
            {
                for(int j = 0;j<3;++j)
                {
                    if(cfg[i][j] >= '0' && cfg[i][j] <= '9')
                    {
                        *(dst++) = cfg[i][j];
                        ++count;
                    }
                   
                }
                
                if(i<2) *(dst++) = ';'; 
            }

            *(dst++) = 'm';
            *(dst++) = c;
            *(dst) = '\0';

            return count;
        }    

        // formats buffor background and returns counted chars (14 up to 20)
        int formatBgOut(char* dst,Color bg,char c)
        {
            const char* num2 = "\033[48;2;"; // 7 ( 7 - 13)
            int count = 11;

            char bfg[3][3];
            
            itoch(bg.r,bfg[0]);
            itoch(bg.g,bfg[1]);
            itoch(bg.b,bfg[2]);


            for(int i = 0; i < 7; ++i)
            {
                *(dst++) =  num2[i];
            }
            
            for(int i = 0; i < 3; ++i)
            {
                for(int j = 0;j<3;++j)
                {
                    if(bfg[i][j] >= '0' && bfg[i][j] <= '9')
                    {
                        *(dst++) = bfg[i][j];
                        ++count;
                    }
                    
                }
                
                if(i<2)*(dst++) = ';'; 
            }

            *(dst++) = 'm';
            *(dst++) = c;
            *(dst) = '\0';

            return count;
        }    

        int formatLineOut(char* dst,size_t row)
        {
            int count = 5;

            char x[5];
            itoch(row,x);

            *(dst++) = '\033';
            *(dst++) = '[';

            for(int i = 0;i < 5;++i)
            {
                if(x[i] >= '0' && x[i] <= '9')
                {
                    *(dst++) = x[i];
                    ++count;
                }
            }

            *(dst++) = ';';
            *(dst++) = 'H';
            *(dst) = '\0';

            return count;
        }

    } // namespace core

} // namespace op