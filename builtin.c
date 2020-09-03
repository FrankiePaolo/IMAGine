#  include <stdio.h>
#  include <stdlib.h>
#  include <stdarg.h>
#  include <string.h>
#  include <math.h>
#  include <vips/vips.h>
#  include "utils.h"
#  include "builtin.h"
#  include "eval.h"

struct utils *
   callbuiltin(struct fncall * f) {
      enum bifs functype = f -> functype;
      struct utils * v = eval(f -> l);

      switch (functype) {
      case B_print:
         print_B(v);
         return v;
      case I_width:
         getWidth(((struct symref * ) v));
         return v;
      case I_invert:
         invert(((struct symref * ) v));
         return v;
      case I_average:
         average(((struct symref * ) v));
         return v;
      default:
         yyerror("Unknown built-in function %d", functype);
         return NULL;
      }
   }

void
average(struct symref * v) {
   double mean;
   struct utils * temp1 = v -> s -> value;
   if (vips_avg((((struct img * ) temp1) -> img), & mean, NULL)) {
      vips_error_exit(NULL);
   }

   printf("mean pixel value = %g\n", mean);
}

void
invert(struct symref * v) {
   VipsImage * out;
   char path[500];
   struct utils * temp1 = v -> s -> value;
   if (vips_invert((((struct img * ) temp1) -> img), & out, NULL)) {
      vips_error_exit(NULL);
   }

   printf("Please enter the path of the output image :\n");
   scanf("%s", path);
   if (vips_image_write_to_file(out, path, NULL)) {
      vips_error_exit(NULL);
   }
   printf("Image saved\n");
}

void
getWidth(struct symref * v) {
   struct utils * temp1 = v -> s -> value;
   printf("image width = %d\n", vips_image_get_width(((struct img * ) temp1) -> img));
}

void
print_B(struct utils * v) {
   struct utils * temp1;
   struct symbol * temp; 
   struct list * li;
   
   if(v -> nodetype == 'N' && ((struct symref * ) v) -> s->li) {
      temp=((struct symref * ) v) -> s;
      li=temp->li;
      do{
         //printf("Pointer:%X Value:%d NodeType:%d\n", li, ((struct integer *)li->e)->i, ((struct utils *)li->e)->nodetype);
         print_B( ((struct utils *)li->e));
      } while(li=li->n);
   }else if (v -> nodetype == 'i') {
      printf("%d\n", ((struct integer * ) v) -> i);
   } else if (v -> nodetype == 'D') {
      printf("%f\n", ((struct doublePrecision * ) v) -> d);
   } else if (v -> nodetype == 'N') {
      temp1 = ((struct symref * ) v) -> s -> value;

      while (temp1->nodetype=='N') {
         temp1=((struct symref * ) temp1) -> s -> value;
      }
      if (temp1->nodetype == 'i') {
         printf("%i\n", ((struct integer * ) temp1) -> i);
      } else if(temp1->nodetype == 'D') {
         printf("%f\n", ((struct doublePrecision * ) temp1) -> d);
      }
   } else {
      printf("Node not found\n");
   }
}