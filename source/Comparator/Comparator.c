/*  @file
 *
 *  @brief      This module handles the Comparator channel
 *
 *  @details    Detailed description of the file contents
 *
 *  @section    Applicable_Documents
 *					List here all the applicable documents if needed. <tr>
 *
 *
 *  @copyright  Copyright 2016- Whirlpool Corporation. All rights reserved - CONFIDENTIAL
 */
//---------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------


//-------------------------------------- Include Files ----------------------------------------------------------------
#include "C_Extensions.h"
#include "Comparator.h"

//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------


//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================

//---------------------------------------------------------------------------------------------------------------------
/**
 *  @brief      It Initializes the  Comparator module and its variables
 *
 */
void Comparator__Initialize(void)
{
	;
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief - This module configures the Comparator channel into desired modes
 * @param channel
 * @param inverted_input - cmp positive input selection
 * @param noninverted_input - cmp negative input selection
 * @param mode - comparator modes
 * @return
 */
PASS_FAIL_TYPE Comparator__Config(COMPARATOR_CHANNEL_DEF channel,COMPARATOR_INVERTED_INPUT_DEF inverted_input,COMPARATOR_NONINVERTED_INPUT_DEF noninverted_input,COMPARATOR_MODE_DEF mode, uint16 cmp_thr)
 {
	PASS_FAIL_TYPE response;

	response = PASS;

return (response);
}

//-----------------------------------------------------------------------------------------------------------
/*
 *
 * @brief This method used for checking the comparator channel output status
 * @param: channel
 * @return: status of comparator
 *
 */
uint8 Comparator__GetStatus(COMPARATOR_CHANNEL_DEF channel)
{
	uint8 status;
	status = 0;
// to be implemented
	return (status);
}


//-----------------------------------------------------------------------------------------------------------
/*
 *
 * @brief This method used to set the comparator threshold
 * @param: channel
 * @return: status of comparator
 *
 */
void Comparator__SetThr(COMPARATOR_CHANNEL_DEF channel, uint16 cmp_thr)
{
	;
}

//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
