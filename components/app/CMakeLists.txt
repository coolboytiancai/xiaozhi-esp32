idf_component_register(
    SRCS "ebook_reader.c" "word_study.c" "pomodoro.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES driver esp_common display esp_timer
)
