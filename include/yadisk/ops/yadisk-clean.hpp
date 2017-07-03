#ifndef YADISK_CLEAN_HPP
#define YADISK_CLEAN_HPP

#include <string>
#include <map>

#include <include/yadisk/ops/Tree.hpp>
#include <include/yadisk/ops/Resource.hpp>
#include <include/yadisk/ops/Predicate.hpp>
#include <yadisk/client.hpp>

// using в header стараемся не использовать, чтобы не возникло коллизии 
// с другими проектами при подключении данного header-а.

namespace yadisk 
{
	namespace ops 
	{
		void clear_duplicate(yadisk::Client& client, yadisk::ops::Predicate pred = yadisk::ops::Hash)
		{
			std::map<std::string, std::vector<yadisk::ops::Resource>> duplicate = ops.find_duplicate(client);
			for(auto it = duplicate.begin(); it != duplicate.end(); ++it)
			{
				for (auto p : it->second)
				{
					if (it->first != p.path)
					{
						client.remove(p.path, true);
						std::cout << "Duplicate founded and deleted!";
					}
				}
			}
		}
	}
}

#endif
