using yadisk::ops::Tree;
using yadisk::ops::Predicate;
using yadisk::ops::Duplicate;
using yadisk::Client;
using std::string;
using std::map;

using Resources = std::vector<Resource>;
 
namespace yadisk 
{
namespace ops 
{
	void clear_duplicate(Client& client, Predicate pred = Hash)
	{
		Map<string, Resources> duplicate = ops.find_duplicate(client);
		
		for(auto it = duplicate.begin(); it!= duplicate.end(); ++it)
		{
			for(int i = 0; i < it->second.size(); ++i)
				if(it->first != it->second[i].path)
				{
					client.remove(it->second[i].path, true);
					std::cout << "Duplicate if founded and deleted!";
				}
		}
	}
}
}
