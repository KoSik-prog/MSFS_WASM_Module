// WASM_Module5.cpp

#include <stdio.h>
#include "WASM_Panels.h"

extern "C" {

#include <MSFS_WindowsTypes.h>
#include <MSFS/MSFS.h>
#include <MSFS/Legacy/gauges.h>
}

extern "C" {
#include "SimConnect.h"

}

extern "C" MODULE_EXPORT void test(void)
{
    // TODO
}

/* Attempt to get SimConnect_CLientDataArea functionality implemented. */
HRESULT hr;
HANDLE hSimConnect;

SIMCONNECT_CLIENT_DATA_ID ClientDataID = 1;
DWORD dwSize = 8;

static enum DATA_DEFINE_ID
{
    DEFINITION_1 = 12,
};

static enum DATA_REQUEST_ID
{
    REQUEST_1 = 10,
};

static enum EVENT_ID
{
    EVENT_RANGE = 1,
};

static enum GROUP_ID
{
    GROUP_A = 1,
};

// MCDU Button calculator codes.
PCSTRINGZ MCDU_BUTTONS[] =  		// Index
{
    "(>H:A320_Neo_CDU_1_BTN_0)",	// 0
    "(>H:A320_Neo_CDU_1_BTN_1)",	// 1
    "(>H:A320_Neo_CDU_1_BTN_2)",	// etc.
    "(>H:A320_Neo_CDU_1_BTN_3)",
    "(>H:A320_Neo_CDU_1_BTN_4)",
    "(>H:A320_Neo_CDU_1_BTN_5)",
    "(>H:A320_Neo_CDU_1_BTN_6)",
    "(>H:A320_Neo_CDU_1_BTN_7)",
    "(>H:A320_Neo_CDU_1_BTN_8)",
    "(>H:A320_Neo_CDU_1_BTN_9)",
    "(>H:A320_Neo_CDU_1_BTN_A)",
    "(>H:A320_Neo_CDU_1_BTN_B)",
    "(>H:A320_Neo_CDU_1_BTN_C)",
    "(>H:A320_Neo_CDU_1_BTN_D)",
    "(>H:A320_Neo_CDU_1_BTN_E)",
    "(>H:A320_Neo_CDU_1_BTN_F)",
    "(>H:A320_Neo_CDU_1_BTN_G)",
    "(>H:A320_Neo_CDU_1_BTN_H)",
    "(>H:A320_Neo_CDU_1_BTN_I)",
    "(>H:A320_Neo_CDU_1_BTN_J)",
    "(>H:A320_Neo_CDU_1_BTN_K)",
    "(>H:A320_Neo_CDU_1_BTN_L)",
    "(>H:A320_Neo_CDU_1_BTN_M)",
    "(>H:A320_Neo_CDU_1_BTN_N)",
    "(>H:A320_Neo_CDU_1_BTN_O)",
    "(>H:A320_Neo_CDU_1_BTN_P)",
    "(>H:A320_Neo_CDU_1_BTN_Q)",
    "(>H:A320_Neo_CDU_1_BTN_R)",
    "(>H:A320_Neo_CDU_1_BTN_S)",
    "(>H:A320_Neo_CDU_1_BTN_T)",
    "(>H:A320_Neo_CDU_1_BTN_U)",
    "(>H:A320_Neo_CDU_1_BTN_V)",
    "(>H:A320_Neo_CDU_1_BTN_W)",
    "(>H:A320_Neo_CDU_1_BTN_X)",
    "(>H:A320_Neo_CDU_1_BTN_Y)",
    "(>H:A320_Neo_CDU_1_BTN_Z)",
    "(>H:A320_Neo_CDU_1_BTN_DIR)",
    "(>H:A320_Neo_CDU_1_BTN_PROG)",
    "(>H:A320_Neo_CDU_1_BTN_PERF)",
    "(>H:A320_Neo_CDU_1_BTN_INIT)",
    "(>H:A320_Neo_CDU_1_BTN_DATA)",
    "(>H:A320_Neo_CDU_1_BTN_FPLN)",
    "(>H:A320_Neo_CDU_1_BTN_NAVRAD)",
    "(>H:A320_Neo_CDU_1_BTN_FUEL)",
    "(>H:A320_Neo_CDU_1_BTN_SEC)",
    "(>H:A320_Neo_CDU_1_BTN_ATC)",
    "(>H:A320_Neo_CDU_1_BTN_MENU)",
    "(>H:A320_Neo_CDU_1_BTN_AIRPORT)",
    "(>H:A320_Neo_CDU_1_BTN_UP)",
    "(>H:A320_Neo_CDU_1_BTN_DOWN)",
    "(>H:A320_Neo_CDU_1_BTN_PREVPAGE)",
    "(>H:A320_Neo_CDU_1_BTN_NEXTPAGE)",
    "(>H:A320_Neo_CDU_1_BTN_L1)",
    "(>H:A320_Neo_CDU_1_BTN_L2)",
    "(>H:A320_Neo_CDU_1_BTN_L3)",
    "(>H:A320_Neo_CDU_1_BTN_L4)",
    "(>H:A320_Neo_CDU_1_BTN_L5)",
    "(>H:A320_Neo_CDU_1_BTN_L6)",
    "(>H:A320_Neo_CDU_1_BTN_R1)",
    "(>H:A320_Neo_CDU_1_BTN_R2)",
    "(>H:A320_Neo_CDU_1_BTN_R3)",
    "(>H:A320_Neo_CDU_1_BTN_R4)",
    "(>H:A320_Neo_CDU_1_BTN_R5)",
    "(>H:A320_Neo_CDU_1_BTN_R6)",
    "(>H:A320_Neo_CDU_1_BTN_PLUSMINUS)",
    "(>H:A320_Neo_CDU_1_BTN_SP)",		// Space
    "(>H:A320_Neo_CDU_1_BTN_DIV)",		// Slash
    "(>H:A320_Neo_CDU_1_BTN_OVFY)",
    "(>H:A320_Neo_CDU_1_BTN_CLR)",
    "(>H:A320_Neo_CDU_1_BTN_BRT_S1)", // Experimental brightness increase (INOP)
    "(>H:A320_Neo_CDU_1_BTN_DIM_S2)", // Experimental brightness decrease (INOP).
    "(>H:A320_Neo_CDU_1_BTN_DOT)",
};

PCSTRINGZ LVAR_EFIS_PANEL[] =  		// A320 EFIS + AUTOPILOT PANEL
{
    "XMLVAR_Baro1_Mode",
    "XMLVAR_Baro_Selector_HPA_1",
    "A32NX_AUTOPILOT_SPEED_SELECTED",  // 1 - auto
    "A32NX_AUTOPILOT_1_ACTIVE",
    "A32NX_AUTOPILOT_2_ACTIVE",
    "A32NX_AUTOTHRUST_STATUS",
    "A32NX_FMA_EXPEDITE_MODE",
    "A32NX_AUTOPILOT_APPR_MODE",
    "A32NX_AUTOPILOT_LOC_MODE",
    "XMLVAR_Autopilot_Altitude_Increment",
    "BTN_LS_1_FILTER_ACTIVE",
    "A32NX_FCU_SPD_MANAGED_DOT",
    "A32NX_FCU_SPD_MANAGED_DASHES",
    "A32NX_FCU_HDG_MANAGED_DOT",
    "A32NX_FCU_HDG_MANAGED_DASHES",
    "A32NX_AUTOPILOT_VS_SELECTED",
    "A32NX_FCU_VS_MANAGED",  // 1 - auto
    "A32NX_AUTOPILOT_HEADING_SELECTED", // HDG
    "A32NX_FCU_ALT_MANAGED",  // 1 - auto
    "A32NX_FCU_APPR_MODE_ACTIVE",
    //"(> L:A32NX_ELEC_DC_ESS_BUS_IS_POWERED)"
};

PCSTRINGZ EVENTS_EFIS_PANEL[] =  		// A320 EFIS + AUTOPILOT PANEL
{
    "(> K:A32NX.FCU_AP_1_PUSH)",
    "(> K:A32NX.FCU_AP_2_PUSH)",
    "(> K:A32NX.FCU_ATHR_PUSH)",
    "(> K:A32NX.FCU_SPD_PUSH)",
    "(> K:A32NX.FCU_SPD_PULL)",
    "(> K:A32NX.FCU_SPD_MACH_TOGGLE_PUSH)",
    "(> K:A32NX.FCU_HDG_PUSH)",
    "(> K:A32NX.FCU_HDG_PULL)",
    "(> K:A32NX.FCU_TRK_FPA_TOGGLE_PUSH)",
    "(> K:A32NX.FCU_ALT_INC)",
    "(> K:A32NX.FCU_ALT_DEC)",
    "(> K:A32NX.FCU_ALT_INCREMENT_SET)",
    "(> K:A32NX.FCU_ALT_PUSH)",
    "(> K:A32NX.FCU_ALT_PULL)",
    "(> K:A32NX.FCU_VS_PUSH)",
    "(> K:A32NX.FCU_VS_PULL)",
    "(> K:A32NX.FCU_LOC_PUSH)",
    "(> K:A32NX.FCU_APPR_PUSH)",
    "(> K:A32NX.FCU_EXPED_PUSH)",
    "(> K:A32NX.FCU_SPD_DEC)",
    "(> K:A32NX.FCU_SPD_INC)",
    "(> K:A32NX.FCU_HDG_DEC)",
    "(> K:A32NX.FCU_HDG_INC)",
    "(> K:A32NX.FCU_VS_DEC)",
    "(> K:A32NX.FCU_VS_INC)",
};

PCSTRINGZ EVENTS_OTHERS[] =  		// INNE EVENTY
{
    "HANDLING_ElevatorTrim",
};

struct DataRefs
{
    double id = 1;  // numer id dla rozroznienia otrzymywanych danych 
    double baro1_mode = 1.;
    double baro_selector_hpa = 1.;
    double autopilot_speed_selected = 1.;
    double autopilot_1_active = 1.;
    double autopilot_2_active = 1.;
    double autothrust_status = 1.;
    double fma_expedite_mode = 1.;
    double autopilot_appr_mode = 1.;
    double autopilot_loc_mode = 1.;
    double autopilot_altitude_increment = 1.;
    double baro_ls = 1.;
    double fcu_speed_dot = 1.;
    double fcu_speed_dashes = 1.;
    double fcu_hdg_dot = 1.;
    double fcu_hdg_dashes = 1.;
    double vs_selected = 1.;
    double fcu_vs_managed = 1.; // 1 - auto
    double autopilot_heading_selected = 1.;
    double fcu_alt_managed = 1.;
    double fcu_app_managed = 1.;
    double elevator_trim = 1.;
    //double dc_bus_power = 1.;
}a32nx_efis;

static void FSAPI EventHandler(ID32 event, UINT32 evdata, PVOID userdata) 
{
    // Any event number from 0x11000 through 0x1FFFF is available, but might collide with other mods.
    switch (event) {
    case 0x11096: {  // eventy z listy EVENTS_OTHERS z parametrem
        UINT8 LVAR_INDEX = (evdata & 0xFF);
        ID idA320 = check_named_variable(EVENTS_EFIS_PANEL[LVAR_INDEX]);
        // Set a value
        FLOAT64 LVAR_VALUE = (evdata & 0xFFFF00) >> 8;
        fprintf(stderr, "Panels: 0x11096 EVENT -> %s   / val: %f.\n", EVENTS_OTHERS[LVAR_INDEX], LVAR_VALUE);
        execute_calculator_code(EVENTS_EFIS_PANEL[LVAR_INDEX], &LVAR_VALUE, nullptr, nullptr);
        break;
    }
    case 0x11097: {  // eventy z listy EVENTS_EFIS_PANEL z parametrem
        UINT8 LVAR_INDEX = (evdata & 0xFF);
        ID idA320 = check_named_variable(EVENTS_EFIS_PANEL[LVAR_INDEX]);
        // Set a value
        FLOAT64 LVAR_VALUE = (evdata & 0xFFFF00) >> 8;
        fprintf(stderr, "Panels: 0x11097 EVENT -> %s   / val: %f.\n", EVENTS_EFIS_PANEL[LVAR_INDEX], LVAR_VALUE);
        execute_calculator_code(EVENTS_EFIS_PANEL[LVAR_INDEX], &LVAR_VALUE, nullptr, nullptr);
        break;
    }
    case 0x11098: {  // eventy z listy EVENTS_EFIS_PANEL
        fprintf(stderr, "Panels: 0x11098 EVENT -> %s\n", EVENTS_EFIS_PANEL[evdata]);
        execute_calculator_code(EVENTS_EFIS_PANEL[evdata], nullptr, nullptr, nullptr);
        break;
    }
    case 0x11099: {    // eventy z listy LVAR_EFIS_PANEL
        UINT8 LVAR_INDEX = (evdata & 0xFF);
        ID idA320 = check_named_variable(LVAR_EFIS_PANEL[LVAR_INDEX]);
        // Set a value
        FLOAT64 LVAR_VALUE = (evdata & 0xFFFF00) >> 8;
        fprintf(stderr, "Panels: 0x11099 EVENT -> %s   / wart: %f.\n", LVAR_EFIS_PANEL[LVAR_INDEX], LVAR_VALUE);
        set_named_variable_value(idA320, LVAR_VALUE);
        break;
    }
    /*case 0x11000: {
        // Press MCDU button DIR
        FLOAT64* a;
        SINT32* b;
        PCSTRINGZ* c;
        fprintf(stderr, "Panels: Wywolano zdarzenie 0x11000\n");
        //execute_calculator_code("(>H:A320_Neo_CDU_1_BTN_DIR)", a, b, c);
        execute_calculator_code(MCDU_BUTTONS[evdata], nullptr, nullptr, nullptr);
        break;
    }
    case 0x11001: {
        // EFIS Panel modes
        UINT8 LVAR_INDEX = (evdata & 0xFF);
        ID idA320 = check_named_variable(LVAR_EFIS_PANEL[LVAR_INDEX]);
        // Set a value
        FLOAT64 LVAR_VALUE = (evdata & 0xFF00) >> 8;
        fprintf(stderr, "Panels: Wywolano 0x11001 = %i   /  %f.\n", LVAR_INDEX, LVAR_VALUE);
        set_named_variable_value(idA320, LVAR_VALUE);
        break;
    }
    case 0x11010: {
        // Press MCDU button DIR
        FLOAT64* a;
        SINT32* b;
        PCSTRINGZ* c;
        execute_calculator_code(CJ4_BUTTONS[evdata], nullptr, nullptr, nullptr);
        break;
    }
    case 0x11020: {
        // Experimental LVAR read back.
        ID lvarID = check_named_variable(LVAR_EFIS_PANEL[0]); // A32NX Range 1 (0...5).
        // Get the value
        FLOAT64 lvarValue;
        lvarValue = get_named_variable_value(lvarID);
        // Now, where to send it?
        fprintf(stderr, "Panels: Wywolano 0x11020 = %i  /   %f.\n", lvarID, lvarValue);

        data.dana1 = lvarValue;
        SimConnect_SetClientData(hSimConnect, ClientDataID, DEFINITION_1, SIMCONNECT_CLIENT_DATA_SET_FLAG_DEFAULT, 0, sizeof(data), &data);

    }*/
    }
}


void CALLBACK myDispatchHandler(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext)   // odczyt zmiennych z listy LVAR_EFIS_PANEL (LVAR_ACCESS.EFIS)
{
    DWORD requestID = pData->dwID;
    switch (requestID)
    {
    case SIMCONNECT_RECV_ID_EVENT:
    {
        SIMCONNECT_RECV_EVENT* evt = (SIMCONNECT_RECV_EVENT*)pData;
        switch (evt->uEventID)
        {
        case EVENT_RANGE: {
            ID lvarID; 
            FLOAT64 lvarValue;
            
            a32nx_efis.baro1_mode = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[0]));
            a32nx_efis.baro_selector_hpa = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[1]));
            a32nx_efis.autopilot_speed_selected = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[2]));
            a32nx_efis.autopilot_1_active = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[3]));
            a32nx_efis.autopilot_2_active = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[4]));
            a32nx_efis.autothrust_status = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[5]));
            a32nx_efis.fma_expedite_mode = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[6]));
            a32nx_efis.autopilot_appr_mode = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[7]));
            a32nx_efis.autopilot_loc_mode = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[8]));
            a32nx_efis.autopilot_altitude_increment = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[9]));
            a32nx_efis.baro_ls = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[10]));
            a32nx_efis.fcu_speed_dot = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[11]));
            a32nx_efis.fcu_speed_dashes = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[12]));
            a32nx_efis.fcu_hdg_dot = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[13]));
            a32nx_efis.fcu_hdg_dashes = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[14]));
            a32nx_efis.vs_selected = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[15]));
            a32nx_efis.fcu_vs_managed = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[16]));
            a32nx_efis.autopilot_heading_selected = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[17]));
            a32nx_efis.fcu_alt_managed = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[18])); 
            a32nx_efis.fcu_app_managed = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[19]));

            a32nx_efis.elevator_trim = get_named_variable_value(check_named_variable(EVENTS_OTHERS[0]));
            //a32nx_efis.dc_bus_power = get_named_variable_value(check_named_variable(LVAR_EFIS_PANEL[18]));

            //fprintf(stderr, "Panels: BUS = %f.\n", a32nx_efis.autopilot_speed_selected);

            SimConnect_SetClientData(hSimConnect, ClientDataID, DEFINITION_1, SIMCONNECT_CLIENT_DATA_SET_FLAG_DEFAULT, 0, sizeof(a32nx_efis), &a32nx_efis);
            break;
        }
        default:
        {
            // No default for now.
            break;
        }
        }
    }
    }
}



// This is called when the WASM is loaded into the system.
extern "C" MSFS_CALLBACK void module_init(void)
{
    register_key_event_handler((GAUGE_KEY_EVENT_HANDLER)EventHandler, NULL);

    hr = SimConnect_Open(&hSimConnect, "Standalone Module", nullptr, 0, 0, 0);
    if (hr == S_OK)
    {
        fprintf(stderr, "Panels WASM module initialized");
        hr = SimConnect_MapClientDataNameToID(hSimConnect, "EFIS_CDA", ClientDataID);
        hr &= SimConnect_AddToClientDataDefinition(hSimConnect, DEFINITION_1, SIMCONNECT_CLIENTDATAOFFSET_AUTO, sizeof(a32nx_efis));
        hr &= SimConnect_CreateClientData(hSimConnect, ClientDataID, sizeof(a32nx_efis), SIMCONNECT_CLIENT_DATA_REQUEST_FLAG_CHANGED);
        /******* Define custom user events. *******/
        // Make the dispatch sensitive to the RANGE event.
        hr &= SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_RANGE, "LVAR_ACCESS.EFIS");
        hr &= SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_A, EVENT_RANGE, true);

        hr &= SimConnect_SetNotificationGroupPriority(hSimConnect, GROUP_A, SIMCONNECT_GROUP_PRIORITY_HIGHEST);

        // Define the callback handler.
        SimConnect_CallDispatch(hSimConnect, myDispatchHandler, NULL);
    }

}

extern "C" MSFS_CALLBACK void module_deinit(void)
{
    fprintf(stderr, "Panels WASM module stopped");
    unregister_key_event_handler((GAUGE_KEY_EVENT_HANDLER)EventHandler, NULL);
    SimConnect_Close(hSimConnect);
}

