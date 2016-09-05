# include <conio.h>
# include <stdio.h>

char Interface()
{ 
     int i,val_y,j,val_y0[15],val_x0[15];
     char c;
     window(10,1,70,25);
     textbackground(BLUE); 
     clrscr();
     textcolor(YELLOW);
     cprintf("\n");
     for(i=0;i<25;i++) cprintf(" ");
     cprintf("main menu\n");
     
     val_y=wherey();
     gotoxy(1,val_y);
     for(i=0;i<5;i++) cprintf(" ");
     for(i=0;i<50;i++) cprintf("*");
     cprintf("\n");
     for(j=0;j<13;j++)
     {
         val_y=wherey();
         gotoxy(1,val_y);
         for(i=0;i<5;i++) cprintf(" ");cprintf("*");val_x0[j]=wherex();val_y0[j]=wherey();
         for(i=0;i<48;i++) cprintf(" ");cprintf("*");
         cprintf("\n");  
      }
      
     val_y=wherey();
     gotoxy(1,val_y);
     for(i=0;i<5;i++) cprintf(" ");
     for(i=0;i<50;i++) cprintf("*");
     cprintf("\n");
     
     gotoxy(val_x0[1],val_y0[1]);
     cprintf(" 1.straight insertion      2.binary insertion "); 
     gotoxy(val_x0[3],val_y0[3]);
     cprintf(" 3.shell's                 4.bubble");
     gotoxy(val_x0[5],val_y0[5]);
     cprintf(" 5.quick                   6.simple selecttion ");
     gotoxy(val_x0[7],val_y0[7]);
     cprintf(" 7.heap                    8.merging ");
     gotoxy(val_x0[9],val_y0[9]);
     cprintf(" 9.radix                   a.reservation system");
     gotoxy(val_x0[11],val_y0[11]);
     cprintf(" b.book administraion      c.puzzle ");
     
     cprintf("\n\n\n");
     val_y=wherey();
     gotoxy(1,val_y);
     for(i=0;i<23;i++) cprintf(" ");
     cprintf("please choose:");
       c=getche(); 
     return c;
  }

void main()
{
   char d;
   d=Interface();
   printf("%c",d);
}