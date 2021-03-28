/***********************************************************************************************************************
 * This file was generated by the S32 Configuration Tools. Any manual edits made to this file
 * will be overwritten if the respective S32 Configuration Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v8.0
processor: S32K144
package_id: S32K144_LQFP100
mcu_data: s32sdk_s32k1xx_rtm_401
processor_version: 0.0.0
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: e8e7d036-2d8a-4479-9ec9-e490a96bb199
  called_from_default_init: true
  selectedCore: core0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Included files 
 ******************************************************************************/
#include "peripherals_edma_config_EDMA.h"

/*******************************************************************************
 * edma_config_EDMA initialization code
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'edma_config_EDMA'
- type: 'edma_config'
- mode: 'general'
- custom_name_enabled: 'true'
- type_id: 'edma'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'EDMA'
- config_sets:
  - edma_driver:
    - settings_edmaUserCfg:
      - userStateStruct: 'dmaController_State'
      - userCfgName: 'dmaController_InitConfig'
      - readOnly: 'true'
      - chnArbitration: 'EDMA_ARBITRATION_FIXED_PRIORITY'
      - haltOnError: 'false'
    - settings_array_edmaChCfg:
      - array_chCfgStructs:
        - 0:
          - chStateStructName: 'dmaControllerChn0_State'
          - chConfigName: 'dmaControllerChn0_Config'
          - chType: 'edma_channel_config_t'
          - virtCh: '0'
          - chPrio: 'EDMA_CHN_DEFAULT_PRIORITY'
          - chReq: 'EDMA_REQ_DISABLED'
          - chCallback: 'NULL'
          - chCallbackParam: 'NULL'
          - enableTrigger: 'false'
    - quick_selection: 'edma_default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/**
 * @page misra_violations MISRA-C:2012 violations
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 8.7, External variable could be made static.
 * The external variables will be used in other source files in application code.
 *
 */
edma_state_t dmaController_State;

edma_chn_state_t dmaControllerChn0_State;

edma_chn_state_t * const edmaChnStateArray[] = {
    &dmaControllerChn0_State,
};

edma_channel_config_t dmaControllerChn0_Config = {
    .channelPriority = EDMA_CHN_DEFAULT_PRIORITY,
    .virtChnConfig = EDMA_CHN0_NUMBER,
    .source = EDMA_REQ_DISABLED,
    .callback = NULL,
    .callbackParam = NULL,
    .enableTrigger = false,
};

const edma_channel_config_t * const edmaChnConfigArray[] = {
    &dmaControllerChn0_Config,
};

const edma_user_config_t dmaController_InitConfig = {
    .chnArbitration = EDMA_ARBITRATION_FIXED_PRIORITY,
    .haltOnError = false
};


