#ifndef DEFINE
#define DEFINE
/* ============================================================== */
// [Import] file path

#define INPUT_FILE_A    "../_input/vas_int_r.csv"
#define INPUT_FILE_B    "../_input/vas_int_r.csv"
#define INPUT_FILE_C    "../_input/vas_int_r.csv"

/* ============================================================== */
// [Export] file path

#define OUTPUT_FILE_A   "../_output/log.csv"
#define OUTPUT_FILE_B   "../_output/log.csv"
#define OUTPUT_FILE_C   "../_output/log.csv"

/* ============================================================== */
// for TCP/IP

#define START           "start"
#define END             "end.."
#define READY           "ready"

/* ============================================================== */
// for pid

#define DT              0.02//[s]
#define PGAIN           1.1
#define IGAIN           0.01
#define DGAIN           0

/* ============================================================== */
#endif//DEFINE