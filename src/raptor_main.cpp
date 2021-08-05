#include <seqan3/argument_parser/all.hpp>

#include <raptor/argument_parsing/build.hpp>
#include <raptor/argument_parsing/search.hpp>
#include <raptor/argument_parsing/shared.hpp>
#include <raptor/argument_parsing/top_level.hpp>
#include <raptor/raptor.hpp>

int main(int argc, char ** argv)
{
    try
    {
        seqan3::argument_parser top_level_parser{"raptor", argc, argv, seqan3::update_notifications::on, {"build", "search"}};
        raptor::init_top_level_parser(top_level_parser);

        raptor::try_parsing(top_level_parser);

        seqan3::argument_parser & sub_parser = top_level_parser.get_sub_parser();
        if (sub_parser.info.app_name == std::string_view{"raptor-build"})
            raptor::run_build(sub_parser);
        if (sub_parser.info.app_name == std::string_view{"raptor-search"})
            raptor::run_search(sub_parser);
    }
    catch (seqan3::argument_parser_error const & ext)
    {
        std::cerr << "[Error] " << ext.what() << '\n';
        std::exit(-1);
    }

    return 0;
}
