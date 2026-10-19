idf_component_register(
    SRCS "ebook_reader.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES driver esp_common display
)
