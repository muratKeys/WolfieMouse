/*
 * config_measurements.h
 *
 *  Created on: Apr 16, 2016
 *      Author: Bumsik Kim
 */

#ifndef CONFIG_MEASUREMENTS_H_
#define CONFIG_MEASUREMENTS_H_

/**
 * # About Micromouse Porject's measurements and speed settings.
 *  We measure speed every 1ms, therefore, for performance we need to use
 *  mm/ms other than m/s.
 *  Also, using mm/ms needs addtional mutiplication operation. So we might need 
 *  to consider using Counts/ms.
 *
 * # Basic facts
 *  1m/s = 1mm/ms (Yeah!)
 *  pulse/rev (from datasheet) = 3520 steps / rev
 *  1816  
 *  Wheel diameter
 *  Size of one cell in the maze = 18cm = 180mm
 */
/**
 * Encoder measurements
 */
#define CONFIG_CNT_PER_REV      3520
#define CONFIG_CNT_PER_CELL     360.1448
#define CONFIG_CNT_PER_90_DEG 	223.053
#define CONFIG_LEN_PER_CNT      0.49979

/**
 * Range finder measurements
 */
#define CONFIG_DetectRange	180	/* FIXME: change this */
#define CONFIG_LeftCenter	100
#define CONFIG_RightCenter	100
#define CONFIG_FrontWallRange 52
#define CONFIG_RangeOffset	0	/* the offset between left and right sensor when mouse in the middle of cell */


/**
 * PID control
 */
#define CONFIG_DEFAULT_KP	0.9
#define CONFIG_DEFAULT_KD	0.2

#endif /* CONFIG_MEASUREMENTS_H_ */
