/*

Author: STEVE LEWIS - 2021  PROVIDED FOR PUBLIC DOMAIN USE

contact.steve.usa@gmail.com

https://www.atarimagazines.com/compute/issue38/098_1_ALL_ABOUT_THE_COMMODORE_USR_COMMAND.php


I am trusting that information at the following article is correct:

https://www.universetoday.com/15462/how-far-are-the-planets-from-the-sun/

From which, is summarized the following data:

             milKM milMI AU
Mercury      46    29    0.307   CLOSEST
             70    43    0.466   FARTHEST
						 57    35    0.387   AVERAGE
						 
Venus        107   66    0.718
             109   68    0.728
						 108   67    0.722
						 
Earth        147   91    0.980
             152   94    1.010
						 150   93    1.000
						 
Mars         205   127   1.380
             249   155   1.660
						 228   142   1.520
						 
Jupiter      741   460   4.950
             817   508   5.460
						 779   484   5.200						
						 
Saturn       1350  839   9.050
             1510  938   10.12
						 1430  889   9.580
						 
Uranus       2750  1710  18.40
             3000  1860  20.10
						 2880  1790  19.20
						 
Neptune      4450  2770  29.80
             4550  2830  30.40
						 4500  2800  30.10
						 						 
Pluto        4440  2760  29.70
             7380  4590  49.30
						 5910  3670  39.50
						 
						 
SAMPLE OUTPUT:
					 
1234567890123456789012345678901234567890
work distance (ft) [50]:

defaulted
(1/n near, 2/f far, 4/a avg) [7]: 
defaulted
number of planets to model [8]: 
defaulted
first 8 planets
scaled to 50 ft
        nearest   farthest  average   
mercury 000' 006" 000' 009" 000' 007" 
venus   001' 001" 001' 002" 001' 002" 
earth   001' 007" 001' 007" 001' 007" 
mars    002' 002" 002' 008" 002' 006" 
jupiter 008' 001" 008' 011" 008' 006" 
saturn  014' 009" 016' 006" 015' 008" 
uranus  030' 002" 032' 010" 031' 007" 
neptune 048' 011" 050' 000" 049' 005" 

*/

// PROGRAM COMPILE OPTIONS
//#define USE_GETS           //< Enable to use gets(xxx) versus fgets(xxx)
//#define SSC_TEST_MODE      //< Enable this for quick testing of cases without prompting for any input
#define ABBREVIATED_MODE   //< Enable to skip repeating the reference data during output
#define LIMITED_SCALE      //< Limit max scale to approximately ~2^32 (unsigned 32-bit); useful if no sscanf to convert float to string, or don't want to deal with rough precision with massive numbers that can't be perfectly represented in a float-type

#include <stdio.h>             //< printf, scanf
#include <string.h>            //< strlen
#include <stdlib.h>            //< strtoul

#define TRUE 1

#define NUM_PLANETS 9
char planet_names[NUM_PLANETS][8] = {
	{"mercury\0"},
	{"venus\0"},
	{"earth\0"},
	{"mars\0"},
	{"jupiter\0"},
	{"saturn\0"},
	{"uranus\0"},
	{"neptune\0"},
	{"pluto\0"}
};

#define INDEX_NEAREST  0
#define INDEX_FARTHEST 1
#define INDEX_AVERAGE  2

#define INDEX_MIL_KM   0  // Millions of KM
#define INDEX_MIL_MI   1  // Millions of Miles
#define INDEX_AU       2  // Astronomical Unit  (Sun to Earth distance)

float planet_distance_data[9*3][3] = {   //< 9 planets, 3 rows of data per planet, 3 columns of data per row
// milKM     milMI     AU
// MERCURY
	{46.0f,    29.0f,    0.307f},  // NEAREST
	{70.0f,    43.0f,    0.466f},  // FARTHEST
	{57.0f,    35.0f,    0.387f},  // AVERAGE
// VENUS
  {107.0f,   66.0f,    0.718f},
	{109.0f,   68.0f,    0.728f},
	{108.0f,   67.0f,    0.722f},
// EARTH						 
  {147.0f,   91.0f,    0.980f},
	{152.0f,   94.0f,    1.010f},
	{150.0f,   93.0f,    1.000f},
// MARS						 
  {205.0f,   127.0f,   1.380f},
	{249.0f,   155.0f,   1.660f},
	{228.0f,   142.0f,   1.520f},
// JUPITER						 
  {741.0f,   460.0f,   4.950f},
	{817.0f,   508.0f,   5.460f},
	{779.0f,   484.0f,   5.200f},
// SATURN						 
  {1350.0f,  839.0f,   9.05f},
	{1510.0f,  938.0f,   10.12f},
	{1430.0f,  889.0f,   9.58f},
// URANUS						 
  {2750.0f,  1710.0f,  18.4f},
	{3000.0f,  1860.0f,  20.1f},
	{2880.0f,  1790.0f,  19.2f},
// NEPTUNE						 
  {4450.0f,  2770.0f,  29.8f},
	{4550.0f,  2830.0f,  30.4f},
	{4500.0f,  2800.0f,  30.1f},
// PLUTO
  {4440.0f,  2760.0f,  29.7f},
	{7380.0f,  4590.0f,  49.3f},
	{5910.0f,  3670.0f,  39.5f}
};		

// REMINDER: When adjusting any of the constants, search the code and spot check any impacts...
#define DEFAULT_WORK_DISTANCE_FT    50.0f
#define DEFAULT_NUM_PLANETS         8U
#define DISTANCE_TYPE_NONE          0U
#define DISTANCE_TYPE_FIRST         1U
#define DISTANCE_TYPE_NEAREST_MASK  1U
#define DISTANCE_TYPE_FARTHEST_MASK 2U
#define DISTANCE_TYPE_AVERAGE_MASK  4U
#define DISTANCE_TYPE_MAX           (DISTANCE_TYPE_NEAREST_MASK | DISTANCE_TYPE_FARTHEST_MASK | DISTANCE_TYPE_AVERAGE_MASK)
#define MIN_SUPPORTED_WORK_DISTANCE 0.001f

#ifdef LIMITED_SCALE	
	#define MAX_SUPPORTED_WORK_DISTANCE 4000000000.0f  //< Float can go higher, but 32-bit limited input can't
#else
  #define MAX_SUPPORTED_WORK_DISTANCE 400000000000000.0f  //< Float can go higher, but the uniform output can't                                                                        
#endif	
	
#define ROUNDOFF                    0.5f
#define THREE_DIGIT_DECIMAL         1000.0f 
#define SIX_DIGIT_DECIMAL           1000000.0f

#define MAX_INPUT_BUFFER_SIZE 40  
// The above buffer supports keying crazy input like:
// "123456789.987654321" 
// "3.141592653589793238462643383279502884"
   // 10000000000000000000
	 // 100000000
// "399999999999999.9998887776665554443332"
// "399999900000000.9988776655"
//  1234567890123456789012345678901234567890
// Supporting up to "1-screen-width" worth of digits plus decimal.

#define INPUT_ENTER    '\n' // 0x0A / 10  (newline is 13, 0x0C)
#define INPUT_SPACE    ' '  // 0x20 / 32
#define INPUT_DECIMAL  '.'

#ifndef SSC_TEST_MODE
static char input_str[MAX_INPUT_BUFFER_SIZE];                                   
static char distance_str[MAX_INPUT_BUFFER_SIZE];                                   
#endif

#ifndef ABBREVIATED_MODE		
// This is a special function just to handle "padding" of the FRAC portion of the AU values.
// These FRAC portions are normally 1, 2, or 3 digits (as the AU data as given).  Since we're 
// showing it as an integer past the decimal, we pad by multiplying the value by 10 until it has 5 digits.
// NOTE: Only place this function falls apart is when the FRAC value is 0.  And this only
// happens for Earth, where the average AU distance for Earth is by definition exactly 1.0
// A 0-value can't be padded, we need at least 1 non-zero digit to multiply by 10.
unsigned int pad_to5(unsigned int value)
{
	unsigned int multiplier = 10000;  //< This function is specialized to 5-digit pad
	if (value > 0)
	{		
		if (value < multiplier)
		{
			while (value < multiplier) 
			{
				value *= 10;				
			}
		}
		/* NOT USED - but this concept could be used to "reduce" an integer being used past a decimal to less than N-digits (keep this around in case the AU constants get adjusted to more than 3 digits past decimal)
		else
		{
			while (value > multiplier) 
			{
				value /= 10;
			}
		}
		*/
	}
	// else - no practical way to pad a 0, leave it be...
	return value;
}
#endif

void main()
{

	float work_distance_ft;
	unsigned char distance_type;  // 1/N/n Nearest, 2/F/f Farthest, 4/A/a Average
	unsigned char number_of_planets_to_model;
	
	float distance_percentage;
	float distance_proportion_ft;
	
	// unsigned int 16-bit for cc65 6502 platform  0x     FFFF == 65535 dec
	// unsigned int 32-bit for       x86 platform  0xFFFF FFFF == 4294967295 dec
	unsigned int distance_INT;    
	unsigned int distance_FRAC;  
		
	unsigned char n;	
	unsigned char working_distance_mask;
	unsigned char max_planet_distance_data_index;
	unsigned char job_to_do;	
	unsigned char temp_index;
	unsigned char i;	
	
	char c;
	char* p;
	float v;
	float d;
	
	// DIAMETER OF EARTH = 41.804 million′ = 41804000 ft
	//                                     4294967296 (max unsigned 32-bit, in ft this is ~100x larger than diameter of the Earth)
	// DIAMETER OF SOLAR SYSTEM = 287.46 billion km  (to Sedna)
	// DISTANCE FROM SUN TO PLUTO = 3.67 billion miles (average)	
	// DISTANCE FROM SUN TO NEPTUNE = 2.781 billion mi      == 14,683,680,000,000 feet
	// MIN/MAX OF FLOAT == 1.175494351 E-38	3.402823466 E+38
	
	// 1 AU   =              4.908e+11 ft
	// 1 AU   =        490,806,662,372.05 ft  (http://convert-to.com/conversion/length/convert-au-to-ft.html)
	// 10 AU  =      4,908,066,623,720.5  ft
	// 100 AU =     49,080,666,237,205.0  ft   == 14,959,787,069.1 KM
	//              14,683,680,000,000    ft  (radius of Neptune)   14683680000000
	//             400,000,000,000,000.0  ft  MAX SUPPORTED  (27X the radius of Neptune, 400 div 14.6)		
	
	// 1 LY   = 31,039,143,016,731,900    ft
	//        =      5,878,499,810,000    miles	
	                       
	//work_distance_ft = 4000000000.0f;  // threshold of ft ich to AU	
	//work_distance_ft = 5000000.0f;  // threshold of ft ich to EARTH-DIAMETER
	//work_distance_ft = 10000.0f;  // threshold of ft ich to miles
	//work_distance_ft = 41804000.0f;  // Diameter of Earth in FT
	//work_distance_ft = 14683680000000;  // Sun to Neptune in FT (typical)
	
#ifdef SSC_TEST_MODE

	work_distance_ft = MAX_SUPPORTED_WORK_DISTANCE;
	distance_type = 7;
	number_of_planets_to_model = 8;	
	
#else
	
start_over:

	distance_str[0] = '\0';  //< Make the distance_str BLANK by default
	while (TRUE)
	{
	  printf("work distance (ft) [50]:\n");  //< The \n here is intentional, in case they need to type a very large number (or one with a lot of post-decimal digits) -- e.g. "123456789.987654321" the screen is only 40 columns wide (fitting the question and this number on same row isn't clean)
#ifdef USE_GETS
		gets(distance_str);
#else
		fgets(distance_str, MAX_INPUT_BUFFER_SIZE, stdin);
#endif
		if (distance_str[0] == INPUT_ENTER) distance_str[0] = '\0';       // ENTER (if they press ENTER, force use of default)
		else if (distance_str[0] == INPUT_SPACE) distance_str[0] = '\0';  // SPACE (if they started with pressing space, force use of default)
		n = strlen(distance_str);
		if (n == 0)
		{
			printf("defaulted\n");
			strcpy(distance_str, "50");  //< This is done just so that the default value is output below
			//work_distance_ft = DEFAULT_WORK_DISTANCE_FT;			
		}
		else
		{
			
			//distance_str[n-1] = '\0';  //< Remove the CR/ENTER, since we re-use this string during output below  
			// The code below is a more robust than the above, in case they did silly things like typing SPACE after the digits, etc...
			while (TRUE)
			{
				--n;  // We know they at least pressed RETURN - search for the last valid digit or decimal that was entered
				if (
				  ((distance_str[n] >= '0') && (distance_str[n] <= '9'))
					|| (distance_str[n] == INPUT_DECIMAL)  // decimal
			  )
				{
					distance_str[n+1] = '\0';
					break;
				}				
			}
		}
			
		work_distance_ft = (float)strtoul(distance_str, &p, 10);
		v = 0.0f;
		d = 1.0f;				
		if ((*p) == INPUT_DECIMAL)  //< user typed a decimal, apply that portion as the FRACtional
		{			
			c = *(++p);  // Thanks to vbc for showing this approach (as an alternative to using sscanf)
			while ((c >= '0') && (c <= '9'))
			{
				v = (v * 10.0f) + (c - '0');  // build up as a "big number"
				d *= 10.0f;                   // prepare denominator to scale it back to a "small number"
				if (d >= 1000000000.0f)
				{
					break;  // any more than this, and they're starting to lose float-precision anyway
				}
				c = *(++p);              // move to next input character; should eventually encounter the \0 null
			}
		}
#ifdef LIMITED_SCALE
	  printf("%lu\n+(%lu/%lu)\n", 
			(unsigned long)work_distance_ft, 
			(unsigned long)v, 
			(unsigned long)d
		);
#else
		printf("%.0f\n+(%.0f/%.0f)\n", work_distance_ft, v, d);
#endif		
		work_distance_ft += (v / d);  //< 0, no impact, if no decimal was specified
		
		// Now do the range checking...
		if (
		  (work_distance_ft < MIN_SUPPORTED_WORK_DISTANCE)
			|| (work_distance_ft > MAX_SUPPORTED_WORK_DISTANCE)  //< While FLOAT can support larger, our table output can't.
		)
		{
#ifdef LIMITED_SCALE
      printf("invalid [min 0.001, max 4e9]\n");			
#else
	    printf("invalid [min 0.001, max 4e14]\n");
#endif
		}
		else
		{
			break;
		}
	}
	
	input_str[0] = '\0';  //< Make the input_str BLANK by default
	while (TRUE)
	{
		distance_type = DISTANCE_TYPE_NONE;		        
	  printf("(1/n near, 2/f far, 4/a avg) [%u]: ", DISTANCE_TYPE_MAX);
#ifdef USE_GETS
		gets(input_str);
#else
		fgets(input_str, MAX_INPUT_BUFFER_SIZE, stdin);
#endif
		if (input_str[0] == INPUT_ENTER) input_str[0] = '\0';       // ENTER (if they press ENTER, force use of default)
		else if (input_str[0] == INPUT_SPACE) input_str[0] = '\0';  // SPACE (if they started with pressing space, force use of default)
		n = strlen(input_str);
		if (n == 0)
		{
			printf("defaulted\n");
			distance_type = DISTANCE_TYPE_MAX;
		}
		else
		{
			sscanf(input_str, "%c", &distance_type);  // First see if they entered a character (N/F/A)
  		if (
				(distance_type == 'N')
				|| (distance_type == 'n')
			) 
			  distance_type = DISTANCE_TYPE_NEAREST_MASK;
			else if (
				(distance_type == 'F')
				|| (distance_type == 'f')
			) 
			  distance_type = DISTANCE_TYPE_FARTHEST_MASK;
			else if (
				(distance_type == 'A')
				|| (distance_type == 'a')
			) 
			  distance_type = DISTANCE_TYPE_AVERAGE_MASK;
			else 
				distance_type -= '0';  //< Interpret as an ASCII 0-9 input and shift it back into a numerical 0-9 input  (assumes 0-9 are sequential in the character set)
		}
		
		// Now do the range checking...
		if (
		  (distance_type == DISTANCE_TYPE_NONE)
		  || (distance_type > DISTANCE_TYPE_MAX)  // 0000 0111  (3 options)
		)
		{
			printf("invalid (%u) [max %u]\n", distance_type, DISTANCE_TYPE_MAX);
		}
		else
		{
			break;
		}
	}
	
	input_str[0] = '\0';  //< Make the input_str BLANK by default
	while (TRUE)
	{
		printf("number of planets to model [%u]: ", DEFAULT_NUM_PLANETS);
#ifdef USE_GETS
		gets(input_str);
#else
		fgets(input_str, MAX_INPUT_BUFFER_SIZE, stdin);
#endif
		if (input_str[0] == INPUT_ENTER) input_str[0] = '\0';       // ENTER (if they press ENTER, force use of default)
		else if (input_str[0] == INPUT_SPACE) input_str[0] = '\0';  // SPACE (if they started with pressing space, force use of default)
		n = strlen(input_str);
		if (n == 0)
		{
			printf("defaulted\n");
			number_of_planets_to_model = DEFAULT_NUM_PLANETS;
		}
		else	
		{
			sscanf(input_str, "%c", &number_of_planets_to_model);
			number_of_planets_to_model -= '0';  //< Interpret as an ASCII 0-9 input and shift it back into a numerical 0-9 input  (assumes 0-9 are sequential in the character set)
		}
		
		// Now do the range checking...
		if (
		  (number_of_planets_to_model < 1)
			|| (number_of_planets_to_model > NUM_PLANETS)
		)
		{
			printf("invalid (%u)\n", number_of_planets_to_model);			
		}
		else
		{
			break;
		}
	}	
#endif
	
	// ******************************************************************
	// OUTPUT
	// ******************************************************************

#ifndef SSC_TEST_MODE	        
	printf("first %u planets\n", number_of_planets_to_model);
	
  #ifdef LIMITED_SCALE
	  printf("scaled to %lu.%lu ft\n", (unsigned long)work_distance_ft, (unsigned long)v);
  #else
  	printf("scaled to %f ft\n", (float)work_distance_ft);
  #endif
#endif	
	/* alternative:  
	we avoid the need for the following by using %s to just echo what the user requested in the first place
	kind of cheap, since it won't reveal any internal because-we're-binary round off issues
	(i.e. certain inputs can't be perfectly represented in a float)
	if (work_distance_ft > (float)UINT_MAX)  
	{
		printf("REALLY_FAR...\n");  //< Don't bother trying to convert it to a string, good enough to acknowledge that it's "really big"
	}
	else
	{
	  distance_INT = (unsigned int)work_distance_ft;
	  distance_FRAC = ((work_distance_ft - (float)distance_INT) * 1000) + ROUNDOFF;	
	  printf("%u.%u ft...\n", 
		  distance_INT,
		  distance_FRAC
	  );
	}
	*/
	
	max_planet_distance_data_index = (number_of_planets_to_model-1)*3;	  //< "*3" is because there is 3 rows of data per planet (-1 since the data-array is 0-index based)
	
	// -- OUTPUT HEADER -----------------------
  printf("        ");  //< 8-spaces
	working_distance_mask = DISTANCE_TYPE_NEAREST_MASK;	
	while (TRUE)
	{
		job_to_do = (distance_type & working_distance_mask);
		
		if (job_to_do > 0)  //< Only output the chosen context (NEAREST, FARTHEST, or AVERAGE; any combination is permitted)
		{
			if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
			else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
			else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;			
			
			switch (temp_index)
			{
				                       //  1234567890
			case INDEX_NEAREST:  printf("nearest   "); break;
			case INDEX_FARTHEST: printf("farthest  "); break;
			case INDEX_AVERAGE:  printf("average   "); break;
			default:             printf("error     "); break;
			}			
		}
		
		working_distance_mask <<= 1;
		if (working_distance_mask > DISTANCE_TYPE_MAX)
		{
			break;
		}										
	}
	printf("\n");
	// -------------------------------------------
		
  for (i = 0; i < number_of_planets_to_model; ++i)
	{
		printf("%-8s", planet_names[i]);  //< Lucky all the planet names are less than 8 characters!
		
		working_distance_mask = DISTANCE_TYPE_FIRST;	
		while (TRUE)
		{
			job_to_do = (distance_type & working_distance_mask);
			
			if (job_to_do > 0)  //< Only output the chosen context (NEAREST, FARTHEST, or AVERAGE; any combination is permitted)
			{
				if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
				else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
				else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;			
				
				distance_percentage = 
					planet_distance_data[(i*3)+temp_index][INDEX_MIL_MI]    //< "*3" is because there are 3 rows of data per planet, so we need to offset accordingly
						/
					planet_distance_data[max_planet_distance_data_index+INDEX_FARTHEST][INDEX_MIL_MI];
					
				distance_proportion_ft = distance_percentage * work_distance_ft;				
								
        // The reasons for the following output-unit adjustment is to accommodate
				// "normalizing" the display output format (where the data fits within 9
				// columns plus a seperating space).  This also scales the numeric value
				// into something that can fit within a 16-bit integer (since the largest
				// numeric value is "999", e.g. "999.999xx " (technically need only 10-bit
				// per INT and FRAC portion).  This approach avoids more time consuming
				// FLOAT to STRING conversion, but care must be taken in choosing the
				// unit adjustment thresholds.
				
#ifndef LIMITED_SCALE
				if (work_distance_ft >= 40000000000.0f)
				{   // valid until  400000000000000.0f then need another larger unit (to keep integer portion of output to "999")
			
					// SWITCH TO UNITS OF AU					
					distance_proportion_ft /= 490806662401.57f;
					distance_INT = (unsigned int)distance_proportion_ft;
				  distance_FRAC = (unsigned int)(((distance_proportion_ft - (float)distance_INT) * THREE_DIGIT_DECIMAL) + ROUNDOFF);
										
					printf("%03u.%03uau ", distance_INT, distance_FRAC);										
          //        ^    ^
          //        |    +-- this is because we scaled to 3-digits (*1000.0) earlier  (if change to 1, 2, 4 digit, this will need to change also)				
					//        +------- this is to pad the INT portion to 3-digit, and the value should not exceed 3-digit "999" (moderated by the chosen scale of the output units) 
					
					//was:
					//printf("%07.3fau ", distance_proportion_ft / 490806662401.57f);					
				}                         
				else 
#endif
				if (work_distance_ft >= 5000000.0f) 
				{
					// SWITCH TO UNITS OF EARTH-DIAMETER
					distance_proportion_ft /= 41804000.0f;
					distance_INT = (unsigned int)distance_proportion_ft;
				  distance_FRAC = (unsigned int)(((distance_proportion_ft - (float)distance_INT) * THREE_DIGIT_DECIMAL) + ROUNDOFF);
					
					printf("%03u.%03ued ", distance_INT, distance_FRAC);															
					
					//was:
					//printf("%07.3fed ", distance_proportion_ft / 41804000.0f);
				}
				else if (work_distance_ft >= 999.0f)  //< 999.99 would get rounded to 1000... Trying to avoid 4-digit or wider outputs
				{
					// SWITCH TO MILES
					distance_proportion_ft /= 5280.0f;
					distance_INT = (unsigned int)distance_proportion_ft;
				  distance_FRAC = (unsigned int)(((distance_proportion_ft - (float)distance_INT) * THREE_DIGIT_DECIMAL) + ROUNDOFF);
					
					printf("%03u.%03umi ", distance_INT, distance_FRAC);															
					
					//was:
				  //printf("%07.3fmi ", distance_proportion_ft / 5280.0);
				}
				else if (work_distance_ft < 4.0f)
				{
					// SWITCH TO mm ("small model" mode)
					distance_proportion_ft *= 304.8f;
					distance_INT = (unsigned int)distance_proportion_ft;
				  distance_FRAC = (unsigned int)(((distance_proportion_ft - (float)distance_INT) * THREE_DIGIT_DECIMAL) + ROUNDOFF);
					
					printf("%03u.%03umm ", distance_INT, distance_FRAC);															
					
					//was:
				  //printf("%07.3fmm ", distance_proportion_ft * 304.8);
				}				
				else  // range of 3 to 999.0 we keep output units in FT
				{			
          // output default of FEET and INCHES			
				  distance_INT = (unsigned int)distance_proportion_ft;
				  distance_FRAC = (unsigned int)(((distance_proportion_ft - (float)distance_INT)) * 12.0f);  //< 12 inches per 1 foot
					if (distance_FRAC == 12)  // if the FRAC happens to round to 12inch, increase FT and zero out inch
					{
						++distance_INT;  //< Trying to avoid allowing this to reach 4-digits (by managing the threshold where we change the output units)
						distance_FRAC = 0;
					}
				  printf("%03u' %03u\" ", distance_INT, distance_FRAC);
				}
			}
			
    	working_distance_mask <<= 1;
			if (working_distance_mask > DISTANCE_TYPE_MAX)
			{
				break;
			}										
		}
		printf("\n");
		
#ifdef ABBREVIATED_MODE		
    // SKIP the data portions - while it's interesting for reference, those interested can look it up or review the code
#else
		printf(" mkm/mmi ");
		working_distance_mask = DISTANCE_TYPE_FIRST;	
		while (TRUE)
		{
			job_to_do = (distance_type & working_distance_mask);
			
			if (job_to_do > 0)  //< Only output the chosen context (NEAREST, FARTHEST, or AVERAGE; any combination is permitted)
			{
				if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
				else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
				else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;
		
				job_to_do = (i*3)+temp_index;  //< "*3" here is because there is 3 rows of data per planet, need to index accordingly
				
				printf("%04u/%04u ", 
				  (unsigned int)planet_distance_data[job_to_do][INDEX_MIL_KM], 
					(unsigned int)planet_distance_data[job_to_do][INDEX_MIL_MI]
			  );

				//was:
				//printf("%04.0f/%04.0f ", 
				//	planet_distance_data[job_to_do][INDEX_MIL_KM],
				//	planet_distance_data[job_to_do][INDEX_MIL_MI]
				//);	
			}

    	working_distance_mask <<= 1;
			if (working_distance_mask > DISTANCE_TYPE_MAX)
			{
				break;
			}								
		}
		printf("\n");

    printf(" au      ");
		working_distance_mask = DISTANCE_TYPE_FIRST; // Revert to the FIRST mask
		while (TRUE)
		{
			job_to_do = (distance_type & working_distance_mask);
			
			if (job_to_do > 0)  //< Only output the chosen context (NEAREST, FARTHEST, or AVERAGE; any combination is permitted)
			{
				if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
				else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
				else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;
		
				job_to_do = (i*3)+temp_index;  //< "*3" is because there is 3 rows of data per planet, need to index accordingly
				
				printf("%03u.%u ",  //< The %u is padded to 5 characters per pad_to5 call (so this output is 10 characters total, except in the "0" case)
				  (unsigned int)planet_distance_data[job_to_do][INDEX_AU], 
					pad_to5(
				    (unsigned int)(((planet_distance_data[job_to_do][INDEX_AU] - (float)distance_INT) * THREE_DIGIT_DECIMAL) + ROUNDOFF)
				  )  
				);  
				
				//was:
				//printf("%09.3f ", 
				//	planet_distance_data[job_to_do][INDEX_AU]				
				//);		
			}
			
    	working_distance_mask <<= 1;
			if (working_distance_mask > DISTANCE_TYPE_MAX)
			{
				break;
			}						
		}
		printf("\n");
#endif
	}			

#ifndef SSC_TEST_MODE	
goto start_over;	
#endif
	
}
