idf_component_register(
    SRCS "4x4_matrix.c"
    INCLUDE_DIRS "include"
    REQUIRES driver
    PRIV_REQUIRES freertos app_events
)