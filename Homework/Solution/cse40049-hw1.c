/*
 * CSE-40049 - Homework #1
 *
 * Author:      Ray Mitchell
 * Date:        5/21/2013
 * System:      Intel(R) Core(TM) i7-3740QM CPU @ 2.70GHz 2.70GHz
 *              16.00 GB RAM
 *              Windows 8 Enterprise (64-bit)
 *
 * Description: Profiles execution speed of random inserts into an array.
 *
 * Output (w/5000 inserts per reading):
          Array size      Seconds per insert
                5000                0.000005
               10000                0.000016
               15000                0.000026
               20000                0.000036
               25000                0.000046
               30000                0.000056
               35000                0.000067
               40000                0.000077
               45000                0.000087
               50000                0.000098
               55000                0.000107
               60000                0.000118
               65000                0.000128
               70000                0.000138
               75000                0.000149
               80000                0.000160
               85000                0.000170
               90000                0.000180
               95000                0.000191
              100000                0.000201
              105000                0.000211
              110000                0.000224
              115000                0.000239
              120000                0.000249
              125000                0.000260
              130000                0.000271
              135000                0.000421
              140000                0.000405
              145000                0.000424
              150000                0.000434
              155000                0.000448
              160000                0.000462
              165000                0.000477
              170000                0.000494
              175000                0.000508
              180000                0.000520
              185000                0.000534
              190000                0.000549
              195000                0.000567
              200000                0.000579
              205000                0.000594
              210000                0.000608
              215000                0.000622
              220000                0.000638
              225000                0.000656
              230000                0.000668
              235000                0.000683
              240000                0.000700
              245000                0.000715
              250000                0.000729
              255000                0.000744
              260000                0.000758
              265000                0.000840
              270000                0.000787
              275000                0.000807
              280000                0.000817
              285000                0.000830
              290000                0.000846
              295000                0.000861
              300000                0.000875
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define READINGS 60
#define INSERTS_PER_READING 5000

int *insert(int *array, int length, int index, int value);

int main()
{
   clock_t startTicks, stopTicks;
   double elapsedSeconds;
   int *array = NULL;  //WHY?
   int length = 0;
   int index, value;
   int i, j;

   /* Seed random number generator */
   srand((unsigned)time(NULL));

   /* Output report header */
   printf("%10s\t%18s\n", "Array size", "Seconds per insert");

   /* Take READINGS readings */
   for (i = 0; i < READINGS; ++i)
   {
      /* Each reading will be taken after INSERTS_PER_READING inserts */
      startTicks = clock();
      for (j = 0; j < INSERTS_PER_READING; ++j)
      {
         index = rand() % (length + 1);
         value = rand();
         if ((array = insert(array, length, index, value)) == NULL)
         {
            fprintf(stderr, "Inert failed, exiting.");
            exit(EXIT_FAILURE);
         }
         ++length;
      }
      stopTicks = clock();

      /* Output reading in tabular format */
      elapsedSeconds = (double)(stopTicks - startTicks) / CLOCKS_PER_SEC;
      printf("%10d\t%18.6f\n", length, elapsedSeconds / INSERTS_PER_READING);
   }

   /* Free the old array */
   free(array);

   return EXIT_SUCCESS;
}

/*-----------------------------------------------------------------------------
* Insert value at index in array.  Return a new array containing this inserted
* value.  Free the old array.
----------------------------------------------------------------------------*/
int *insert(int *array, int length, int index, int value)
{
   int i;
   int *newArray;

   /* Allocate new array containing one more element than old array */
   if (!(newArray = (int *)malloc(sizeof(int) * (length + 1))))   /* O(1) */
   {
      fprintf(stderr, "Out of memory");                           /* O(1) */
      return NULL;                                                /* O(1) */
   }

   /* If old array was empty */
   if (length == 0)                                               /* O(1) */
   {
      newArray[0] = value;                                        /* O(1) */
   }
   /* Else old array was not empty */
   else
   {
      /* Copy array[0, index) to newArray[0, index) */
      for (i = 0; i < index; ++i)                                 /* O(n) */
         newArray[i] = array[i];                                  /* O(1) */

      /* Set newArray[index] to value */
      newArray[index] = value;                                    /* O(1) */

      /* Copy array[index, length) to newArray[index + 1, length + 1 */
      for (i = index; i < length; ++i)                            /* O(n) */
         newArray[i + 1] = array[i];                              /* O(1) */

      /* Free old array */
      free(array);                                                /* O(1) */
   }

   /* Return new array containing inserted value */
   return newArray;                                               /* O(1) */
}
