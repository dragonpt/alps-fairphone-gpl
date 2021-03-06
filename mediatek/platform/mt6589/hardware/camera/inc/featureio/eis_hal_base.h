//! \file  eis_hal_base.h

#ifndef _EIS_HAL_BASE_H_
#define _EIS_HAL_BASE_H_

#include "EIS_Type.h"
#include <inc/hwscenario/IhwScenarioType.h>

//! EIS ratio
#define EIS_FACTOR 120

/**
  * @struct eisHal_config_s
  * @brief EIS config structure
  * @details The width and height are assigned to image size which is sent to EIS HW
*/
typedef struct eisHal_config_s
{
    MUINT32 imageWidth;
    MUINT32 imageHeight; 
} eisHal_config_t;

/**
  *@class EisHalBase 
  *@brief EIS class used by scenario
*/
class EisHalBase 
{
public:

    /**       
         *@brief EisHalBase constructor
       */
    EisHalBase() {}; 

    /**
         *@brief Create EisHalBase object
         *@param[in] userName : user name,i.e. who create EIS object
         *@return
         *-EisHalBase object
       */
    static EisHalBase* createInstance(char const *userName);

    /**
         *@brief Destroy EisHalBase object   
         *@param[in] userName : user name,i.e. who destroy EIS object
       */
    virtual MVOID destroyInstance(char const *userName) = 0;

    /**
         *@brief Config EIS
         *@details Call before pass1
         *@param[in] a_ehwMode : hardware scenario
         *@param[in] a_sEisConfig : size of image sent to EIS (TG out size or size after CDRZ)
         *
       */
    virtual MVOID  configEIS(NSHwScenario::EhwMode a_ehwMode, eisHal_config_t a_sEisConfig) = 0;    

    /**       
         *@brief Execute EIS
         *@return
         *-0 indicates success, otherwise indicates fail
       */
    virtual MINT32 doEIS() = 0;

    /**       
         *@brief Get EIS algorithm result (CMV)
         *@param[in,out] a_CMV_X_Int : EIS algo result of X-direction integer part
         *@param[in,out] a_CMV_X_Flt  : EIS algo result of X-direction float part
         *@param[in,out] a_CMV_Y_Int : EIS algo result of Y-direction integer part
         *@param[in,out] a_CMV_Y_Flt  : EIS algo result of Y-direction float part
         *@param[in,out] a_TarWidth    : EIS width crop size
         *@param[in,out] a_TarHeight   : EIS height crop size
       */
    virtual MVOID getEISResult(MUINT32 &a_CMV_X_Int, 
                                   MUINT32 &a_CMV_X_Flt,
                                   MUINT32 &a_CMV_Y_Int, 
                                   MUINT32 &a_CMV_Y_Flt,
                                   MUINT32 &a_TarWidth,
                                   MUINT32 &a_TarHeight) = 0;

    /**       
         *@brief Get EIS GMV
         *@details The value is 256x
         *@param[in,out] a_GMV_X : x-direction global motion vector between two frames
         *@param[in,out] a_GMV_Y  : y-direction global motion vector between two frames
       */
    virtual MVOID getEISGmv(MUINT32 &a_GMV_X, MUINT32 &a_GMV_Y) = 0;

    /**       
         *@brief Return EIS HW statistic result      
         *@param[in,out] a_pEIS_Stat : EIS_STATISTIC_STRUCT  
       */
    virtual MVOID getEISStatistic(EIS_STATISTIC_STRUCT *a_pEIS_Stat) = 0;
    
protected:

    /**       
         *@brief EisHalBase destructor
       */
    virtual ~EisHalBase() {};    
};


/**
  *@class EisNone 
  *@brief Not support EIS
*/
class EisNone : public EisHalBase
{
public:
    
    EisNone() {}; 

    static EisNone* createInstance() {return new EisNone;};

    virtual MVOID  configEIS(NSHwScenario::EhwMode a_ehwMode, eisHal_config_t a_sEisFactor) {};    

    virtual MINT32 doEIS() {return 0;};

    virtual MVOID getEISResult(MUINT32 &a_CMV_X_Int, 
                                   MUINT32 &a_CMV_X_Flt,
                                   MUINT32 &a_CMV_Y_Int, 
                                   MUINT32 &a_CMV_Y_Flt,
                                   MUINT32 &a_TarWidth,
                                   MUINT32 &a_TarHeight) {a_CMV_X_Int = 0;a_CMV_X_Flt = 0;a_CMV_Y_Int = 0; a_CMV_Y_Flt = 0;a_TarWidth = 0; a_TarHeight = 0;};

    virtual MVOID getEISGmv(MUINT32 &a_GMV_X,MUINT32 &a_GMV_Y) {a_GMV_X = 0;a_GMV_Y = 0;};

    virtual MVOID getEISStatistic(EIS_STATISTIC_STRUCT *a_pEIS_Stat) {};
    
private:
    virtual MVOID destroyInstance(char const *userName)  { delete this; };	
    virtual ~EisNone() {};    	
}; 


#endif

