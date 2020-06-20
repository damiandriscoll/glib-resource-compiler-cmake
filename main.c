#include <stdio.h>
#include <stdbool.h>
#include <gtk/gtk.h>

// this function gets created by glib-compile-resources
GResource *example_get_resource (void);

char *allocResource(GResource *gResource, const char *resourceName, gsize *resourceSize, GError **error) {
    char *buffer = NULL;
    if (
        g_resource_get_info(
                gResource,
                resourceName,
                G_RESOURCE_LOOKUP_FLAGS_NONE,
                resourceSize,
                NULL,
                error
        )
    ) {
        buffer = calloc(*resourceSize + 1, sizeof(char));
    }
    return buffer;
}

bool loadResource(GResource *gResource, const char *resourceName, gsize resourceSize, char **resource, GError **error) {
    gsize bytesRead;
    GInputStream *stream;
    bool result = false;

    stream = g_resource_open_stream(gResource, resourceName, G_RESOURCE_LOOKUP_FLAGS_NONE, error);
    if (stream) {
        if (g_input_stream_read_all(stream, *resource, resourceSize, &bytesRead, NULL, error)) {
            if (bytesRead == resourceSize) {
                result = true;
            }
        }
    }
    return result;
}

/**
 * Load a resource and print its contents to stdout
 * @return int 0 if successful, 1 if not found, 2 if not enough memory, 3 if couldn't be read
 */
int main() {
    GResource * gResource;
    char *resource = NULL;
    const char *resourceName = "/com/example/resource/resource.txt";
    gsize resourceSize;
    GError *error = NULL;
    int result = 0;

    gResource = example_get_resource();
    if (gResource != NULL) {
        resource = allocResource(gResource, resourceName, &resourceSize, &error);
        if (resource) {
            if (loadResource(gResource, resourceName, resourceSize, &resource, &error)) {
                printf("%s", resource);
            } else {
                result = 3;
            }
            free(resource);
        } else {
            result = 2;
        }
    } else {
        printf("error code %d, message: %s\n", error->code, error->message);
        result = 1;
    }
    return result;
}
