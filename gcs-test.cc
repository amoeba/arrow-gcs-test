#include <iostream>
#include <fstream>
#include <string>

#include <arrow/result.h>
#include <arrow/filesystem/gcsfs.h>

int main(int argc, char** argv) {

    if (argc != 3) {
        std::cout << "Usage: test-gcs credentials.json bucket_name" << std::endl;
        return -1;
    }

    std::cout << "Reading credentials file from " << argv[1] << "...";

    std::filesystem::path path(argv[1]);
    std::ifstream file(path, std::ios::in | std::ios::binary);
    std::string content {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
    file.close();

    std::cout << "Done" << std::endl;

    // Set up a GcsFileSystem with our JSON credentials
    auto options = arrow::fs::GcsOptions::FromServiceAccountCredentials(content);
    auto gcs_fs_ = arrow::fs::GcsFileSystem::Make(options);

    // Set up a FileSelector to read from the root of the bucket
    auto selector = arrow::fs::FileSelector();
    selector.base_dir = argv[2];
    selector.recursive = true;
    selector.max_recursion = 16;

    std::cout << "Listing " << selector.base_dir << "..." << std::endl;

    // List and iterate
    auto results = gcs_fs_->GetFileInfo(selector);

    for (auto it = results->begin(); it != results->end(); ++it) {

        std::cout << it->dir_name() << "/" << it->base_name() << std::endl;
    }

    std::cout << "Done" << std::endl;

    return 0;
}
