// Taylor Triggs
// System: Rabbit RCM6700 Interface Board, RCM6700 Minicore Microprocessor
// Language: Dynamic C

#class auto

#define START .5
#define JUMP .05

#define VERTICAL_MAX .7
#define VERTICAL_MIN .2

#define HORIZONTAL_MAX .9
#define HORIZONTAL_MIN .1

#define WAIT .1

#define Y_COORDINATE_BASE 350
#define X_COORDINATE_BASE 400

#define MAX_Y 350
#define MIN_Y -150

#define MAX_X 500
#define MIN_X -300

#define RATIO 1000.0

#define CONTROL 2

#define HERTZ 50

void main()
{
   unsigned long  freq, ideal;
   int pwm_options, err;
   int i = 0;
   char input;
   char *dummy;
   float vertical_percent;
   float horizontal_percent;

   int x, y;

   // request 10kHz PWM cycle (will select closest possible value)

   freq = pwm_init(HERTZ);
   printf("Actual PWM frequency = %lu Hz (ideal %lu Hz)\n", freq, HERTZ);

   // Select PWM output port
   pwm_options = PWM_USEPORTE;

   if (vertical_percent != START || horizontal_percent != START)
   {
	      printf("NOT EQUAL TO .5 \n\n");
	      vertical_percent = START;
	      printf("vertical:%f%\n", vertical_percent);

	      horizontal_percent = START;
	      printf("Horizontal:%f%\n\n\n", horizontal_percent);
	}

   printf("Actual PWM frequency = %lu Hz\n", freq);

   printf("vertical:%f%\n", vertical_percent);
	printf("Horizontal:%f%\n\n\n", horizontal_percent);

	err = pwm_set(1, (int)(vertical_percent * 1024.0), pwm_options);

	if(err < 0)
		printf("Error, channel 0.\n");

	err = pwm_set(2, (int)(horizontal_percent * 1024.0), pwm_options);

	if(err < 0)
		printf("Error, channel 0.\n");

#if CONTROL == 1
    while(1) //keep running the program
   	{
	      costate //move
	      {
	         waitfor(kbhit());

	         switch(getchar())
	         {
	         //move up
	         case 'w': vertical_percent += JUMP;
	            if(vertical_percent > VERTICAL_MAX)
	            {
	               vertical_percent = VERTICAL_MAX;
	            }
	            break;

	         //move down
	         case 's': vertical_percent -= JUMP;
	            if(vertical_percent < VERTICAL_MIN)
	            {
	               vertical_percent = VERTICAL_MIN;
	            }
	            break;

	         //move left
	         case 'a': horizontal_percent += JUMP;
	            if(horizontal_percent > HORIZONTAL_MAX)
	            {
	               horizontal_percent = HORIZONTAL_MAX;
	            }
	            break;

	         //move right
	         case 'd': horizontal_percent -= JUMP;
	            if(horizontal_percent < HORIZONTAL_MIN)
	            {
	               horizontal_percent = HORIZONTAL_MIN;
	            }
	            break;

	         default: printf("Invalid input!\n");
	            break;
	         }

	         printf("vertical:%f%\n", vertical_percent);
	         printf("Horizontal:%f%\n", horizontal_percent);

	         err = pwm_set(1, (int)(vertical_percent * 1024.0), pwm_options);

	         if(err < 0)
	            printf("Error, channel 0.\n");

	         err = pwm_set(2, (int)(horizontal_percent * 1024.0), pwm_options);

	         if(err < 0)
	            printf("Error, channel 0.\n");
	      }
	   }
#endif
#if CONTROL == 2
		dummy = malloc(sizeof(char) * 10);

      x = 0;
      y = 0;

      while(1)
      {
         //convert coordinates to PMW
         horizontal_percent = (float)(X_COORDINATE_BASE + x) / RATIO;
         vertical_percent = (float)(Y_COORDINATE_BASE + y) / RATIO;

         //keep PWM in predefined bounds
         if(horizontal_percent > HORIZONTAL_MAX)
         	horizontal_percent = HORIZONTAL_MAX;
          
         else if( horizontal_percent < HORIZONTAL_MIN)
         	horizontal_percent = HORIZONTAL_MIN;

         if(vertical_percent > VERTICAL_MAX)
         	vertical_percent = VERTICAL_MAX;
          
         else if(vertical_percent < VERTICAL_MIN)
         	vertical_percent = VERTICAL_MIN;

         //set PWM
         err = pwm_set(1, (int)(vertical_percent * 1024.0), pwm_options);

	      if(err < 0)
	         printf("Error, channel 0.\n");

	      err = pwm_set(2, (int)(horizontal_percent * 1024.0), pwm_options);

	      if(err < 0)
	         printf("Error, channel 0.\n");

			//inform user about current coordinates
      	printf("\nCurrent Coordinates (%d, %d)\t(%f, %f)\n",
         	(int)((horizontal_percent * RATIO) - X_COORDINATE_BASE),
            (int)((vertical_percent * RATIO) - Y_COORDINATE_BASE),
            horizontal_percent, vertical_percent);

         //get new coordinates
         printf("Enter in new X coordinate\t%d <= X <= %d\n", MIN_X, MAX_X);
         x = atoi(gets(dummy));

         if(x > MAX_X)
         	x = MAX_X;

         else if(x < MIN_X)
         	x = MIN_X;

         printf("\nEnter in new Y coordinate\t%d <= Y <= %d\n", MIN_Y, MAX_Y);
         y = atoi(gets(dummy));

         if(y > MAX_Y)
         	y = MAX_Y;

         else if(y < MIN_Y)
             y = MIN_Y;
      }
#endif
}