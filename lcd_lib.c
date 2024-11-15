        //                                   //  
        //                                   // 
        //              LCD 2x16             // 
        //                                   // 
        //              OSMAN                // 
        //              FARUK                //
        //              AVCI                 //
        //                                   //  
        //                                   //          
        ///////////////////////////////////////
                                                              
                                     
                                 
 #define MY_PORTS
// Alt satýrý portunuza göre tanýmlayýn
// #define USE_PORT_B    
 
#ifdef USE_PORT_B     
   #define LCD_PORT  PORT_B
   #define LCD_TRIS  TRIS_B 
   #define E         PINB0           
   #define RS        PINB1
   #define RW        PINB2                    
   #define data0     PINB4
   #define data1     PINB5                               
   #define data2     PINB6
   #define data3     PINB7  
#elif defined(USE_PORT_D)
   #define LCD_PORT  PORT_D
   #define LCD_TRIS  TRIS_D       
   #define E         PIND0 
   #define RS        PIND1              
   #define RW        PIND2            
   #define data0     PIND4                                     
   #define data1     PIND5
   #define data2     PIND6
   #define data3     PIND7  
#else                                                                        
   #error "LCD BAGLANTISI ICIN PORT SECMELISINIZ (USE_PORT_B veya USE_PORT_D)"   
#endif                                                  
                                                                                
                                       
        
                 
void enable_tetikleme(void){
                                   
    delay_cycles(1);     
    pin_acik(E); 
    delay_cycles(1);         
    pin_kapali(E); 
 
}                 
                                
   
                                          
void lcd_komut(int8 komut){                                 

   LCD_PORT = (komut&0xF0);   
   pin_kapali(RS);             
   enable_tetikleme();         
   delay_ms(2);                       
                                            
   LCD_PORT = (0xF0 &(komut<<4));
   pin_kapali(RS);               
   enable_tetikleme();
   delay_ms(2);     
                                     
}                 
                                                               
void lcd_veri(int8 veri){         
    
   LCD_PORT = (veri&0xF0);
   pin_acik(RS); 
   delay_cycles(1);
   enable_tetikleme();     
   delay_ms(2);                            
                           
   LCD_PORT = (0xF0 &(veri<<4));
   pin_acik(RS);                                                                                                
   enable_tetikleme();                   
   delay_ms(2);                
   
}                           


void imlec(int8 satir , int8 sutun){
                                      
   if(satir == 1)               
      lcd_komut(0x80 | (sutun-1)); 
                                                 
   if(satir == 2)                                    
      lcd_komut(0x80 | (0x40 + (sutun-1)));
}                                         


void lcd_temizle(void){

   lcd_komut(0x01);
                                   
}
 // LCD Kullanmak için bu fonksiyonu lcd ayarlamak için kullan
void lcd_init(void){     

   LCD_TRIS = 0x00;
   int8 i = 0; 
   pin_kapali(RS);     
   pin_kapali(E);
   delay_ms(30);
                                      
   for(i = 0;i <= 3;i++){                                  
                                       
      lcd_komut(0x03);                                      
      delay_ms(5);    
   }                                                                                                     
   lcd_komut(0x02);   // LCD 4 bit haberleþme komutu
   lcd_komut(0x28);   // 2 satýr, 4 bit iletiþim, 5x8 matris seçildi                             
   lcd_komut(0x08);   // Display kapalý, imleç ve yanýp sönme yok                                             
   lcd_komut(0x0F);   // Display Açýk , imleç ve yanýp sönme yok
   lcd_komut(0x06);   // Her veri yazýldýðýnda imleç saða gitsin  
   lcd_komut(0x01);   // Display sil imleç (1,1)
   
}

void lcd_kaydir(int8 kaydir,int1 yon){
   int8 komut;                 
   komut  = 0x18 | (yon<<2);
   for(int i = 0; i<kaydir;i++)          
      lcd_komut(komut);                  
}  
