/*

Author: STEVE LEWIS - 2021  PROVIDED FOR PUBLIC DOMAIN USE

contact.steve.usa@gmail.com

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
 mkm/mmi 0046/0029 0070/0043 0057/0035 
 au      000.30700 000.46600 000.38700 
venus   001' 001" 001' 002" 001' 002" 
 mkm/mmi 0107/0066 0109/0068 0108/0067 
 au      000.71800 000.72800 000.72200 
earth   001' 007" 001' 007" 001' 007" 
 mkm/mmi 0147/0091 0152/0094 0150/0093 
 au      000.98000 001.10000 001.0 
mars    002' 002" 002' 008" 002' 006" 
 mkm/mmi 0205/0127 0249/0155 0228/0142 
 au      001.38000 001.66000 001.52000 
jupiter 008' 001" 008' 011" 008' 006" 
 mkm/mmi 0741/0460 0817/0508 0779/0484 
 au      004.95000 005.46000 005.20000 
saturn  014' 009" 016' 006" 015' 008" 
 mkm/mmi 1350/0839 1510/0938 1430/0889 
 au      009.50000 010.12000 009.58000 
uranus  030' 002" 032' 010" 031' 007" 
 mkm/mmi 2750/1710 3000/1860 2880/1790 
 au      018.40000 020.10000 019.20000 
neptune 048' 011" 050' 000" 049' 005" 
 mkm/mmi 4450/2770 4550/2830 4500/2800 
 au      029.80000 030.40000 030.10000 					 

*/

#include <stdio.h>             //< printf, scanf
#include <string.h>            //< strlen

// PROGRAM COMPILE OPTIONS
//#define USE_GETS           //< Enable to use gets(xxx) versus fgets(xxx)
//#define SSC_TEST_MODE      //< Enable this for quick testing of cases without prompting for any input
#define ABBREVIATED_MODE   //< Enable to skip repeating the reference data during output

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

float planet_distance_data[9*3][3] = {
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
#define MAX_SUPPORTED_WORK_DISTANCE 400000000000000.0f  //< Float can go higher, but the uniform output can't                                                                        
#define ROUNDOFF                    0.5f

#define MAX_INPUT_BUFFER_SIZE 20

#define INPUT_ENTER  0x0A
#define INPUT_SPACE  0x20

#ifndef SSC_TEST_MODE
static char input_str[MAX_INPUT_BUFFER_SIZE];                                   
static char distance_str[MAX_INPUT_BUFFER_SIZE];                                   
#endif

// This is a special function just to handle "padding" of the FRAC portion of the AU values.
// These FRAC portions are normally 1, 2, or 3 digits.  Since we're showing it as an
// integer past the decimal, we pad by multiplying the value by 10 until it has 5 digits.
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
		/* NOT USED - but this concept could be used to "reduce" an integer being used past a decimal to less than N-digits
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

void main()
{

	float work_distance_ft;
	unsigned char distance_type;  // 0/N/n Nearest, 1/F/f Farthest, 2/A/a Average
	unsigned char number_of_planets_to_model;
	
	float distance_percentage;
	float distance_proportion_ft;
	
	// unsigned int 16-bit for cc65 6502 platform  0x     FFFF == 65535
	// unsigned int 32-bit for       x86 platform  0xFFFF FFFF == 4294967295 dec
	unsigned int distance_INT;    
	unsigned int distance_FRAC;  
		
	unsigned char n;	
	unsigned char working_distance_mask;
	unsigned char max_planet_distance_data_index;
	unsigned char job_to_do;	
	unsigned char temp_index;
	unsigned char i;	
	
	// DIAMETER OF EARTH = 41.804 million′ = 41804000 ft
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
	  printf("work distance (ft) [50]:\n");
#ifdef USE_GETS
		gets(distance_str);
#else
		fgets(distance_str, MAX_INPUT_BUFFER_SIZE, stdin);
#endif
		if (distance_str[0] == INPUT_ENTER) distance_str[0] = '\0';  // ENTER
		if (distance_str[0] == INPUT_SPACE) distance_str[0] = '\0';  // SPACE
		n = strlen(distance_str);
		if (n == 0)
		{
			printf("defaulted\n");
			work_distance_ft = DEFAULT_WORK_DISTANCE_FT;
			strcpy(distance_str, "50");
		}
		else
		{			
			distance_str[n-1] = '\0';  // remove the CR/ENTER, since we re-use this string during output later
			sscanf(distance_str, "%f", &work_distance_ft);
		}
		
		// Now do the range checking...
		if (
		  (work_distance_ft < MIN_SUPPORTED_WORK_DISTANCE)
			|| (work_distance_ft > MAX_SUPPORTED_WORK_DISTANCE)  //< While FLOAT can support larger, our table output can't.
		)
		{
			printf("invalid [min 0.001, max 4e14]\n");
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
		if (input_str[0] == INPUT_ENTER) input_str[0] = '\0';  // ENTER
		if (input_str[0] == INPUT_SPACE) input_str[0] = '\0';  // SPACE
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
		if (input_str[0] == INPUT_ENTER) input_str[0] = '\0';  // ENTER
		if (input_str[0] == INPUT_SPACE) input_str[0] = '\0';  // SPACE
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
	printf("scaled to %s ft\n", distance_str);
#endif	
	/* alternative:
	if (work_distance_ft > UINT_MAX)
	{
		printf("REALLY_FAR...\n");
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
	
	max_planet_distance_data_index = (number_of_planets_to_model-1)*3;	
	
  printf("        ");
	working_distance_mask = DISTANCE_TYPE_NEAREST_MASK;	
	while (TRUE)
	{
		job_to_do = (distance_type & working_distance_mask);
		
		if (job_to_do > 0)
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
		
  for (i = 0; i < number_of_planets_to_model; ++i)
	{
		printf("%-8s", planet_names[i]);
		
		working_distance_mask = DISTANCE_TYPE_FIRST;	
		while (TRUE)
		{
			job_to_do = (distance_type & working_distance_mask);
			
			if (job_to_do > 0)
			{
				if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
				else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
				else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;			
				
				distance_percentage = 
					planet_distance_data[(i*3)+temp_index][INDEX_MIL_MI] 
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
								
				if (work_distance_ft >= 40000000000.0f)
				{   // valid until  400000000000000.0f then need another larger unit
			
					// SWITCH TO UNITS OF AU					
					distance_proportion_ft /= 490806662401.57f;
					distance_INT = (unsigned int)distance_proportion_ft;
				  distance_FRAC = (unsigned int)(((distance_proportion_ft - (float)distance_INT) * 1000.0f) + ROUNDOFF);
										
					printf("%03u.%03uau ", distance_INT, distance_FRAC);										
          //        ^    ^
          //        |    +-- this is because we scaled to 3-digits (*1000.0) earlier					
					//        +------- this is to pad the INT portion to 3-digit, and the value should not exceed 3-digit "999" 
					
					//was:
					//printf("%07.3fau ", distance_proportion_ft / 490806662401.57f);					
				}
				else if (work_distance_ft >= 5000000.0f) 
				{
					// SWITCH TO UNITS OF EARTH-DIAMETER
					distance_proportion_ft /= 41804000.0f;
					distance_INT = (unsigned int)distance_proportion_ft;
				  distance_FRAC = (unsigned int)(((distance_proportion_ft - (float)distance_INT) * 1000.0f) + ROUNDOFF);
					
					printf("%03u.%03ued ", distance_INT, distance_FRAC);															
					
					//was:
					//printf("%07.3fed ", distance_proportion_ft / 41804000.0f);
				}
				else if (work_distance_ft >= 999.0f)  //< 999.99 would get rounded to 1000... Trying to avoid 4-digit or wider outputs
				{
					// SWITCH TO MILES
					distance_proportion_ft /= 5280.0f;
					distance_INT = (unsigned int)distance_proportion_ft;
				  distance_FRAC = (unsigned int)(((distance_proportion_ft - (float)distance_INT) * 1000.0f) + ROUNDOFF);
					
					printf("%03u.%03umi ", distance_INT, distance_FRAC);															
					
					//was:
				  //printf("%07.3fmi ", distance_proportion_ft / 5280.0);
				}
				else if (work_distance_ft < 3.0f)
				{
					// SWITCH TO mm
					distance_proportion_ft *= 304.8f;
					distance_INT = (unsigned int)distance_proportion_ft;
				  distance_FRAC = (unsigned int)(((distance_proportion_ft - (float)distance_INT) * 1000.0f) + ROUNDOFF);
					
					printf("%03u.%03umm ", distance_INT, distance_FRAC);															
					
					//was:
				  //printf("%07.3fmm ", distance_proportion_ft * 304.8);
				}				
				else  // range of 3 to 999.0 we keep output units in FT
				{			
          // output default of FEET and INCHES			
				  distance_INT = (unsigned int)distance_proportion_ft;
				  distance_FRAC = (unsigned int)(((distance_proportion_ft - (float)distance_INT)) * 12.0f);
					if (distance_FRAC == 12)  // if the FRAC happens to round to 12inch, increase FT and zero out inch
					{
						++distance_INT;  //< Trying to avoid rolling this to 4-digits
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
			
			if (job_to_do > 0)
			{
				if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
				else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
				else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;
		
				job_to_do = (i*3)+temp_index;
				
				distance_INT = (unsigned int)planet_distance_data[job_to_do][INDEX_MIL_KM];				
				printf("%04u/", distance_INT);
				
				distance_INT = (unsigned int)planet_distance_data[job_to_do][INDEX_MIL_MI];				
				printf("%04u ", distance_INT);

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
			
			if (job_to_do) 
			{
				if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
				else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
				else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;
		
				job_to_do = (i*3)+temp_index;
				
				distance_INT = (unsigned int)planet_distance_data[job_to_do][INDEX_AU];
				distance_FRAC = pad_to5(
				  (unsigned int)(((planet_distance_data[job_to_do][INDEX_AU] - (float)distance_INT) * 1000.0f) + ROUNDOFF)
				);				
				printf("%03u.%u ", distance_INT, distance_FRAC);
				
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