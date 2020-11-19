#include "../../lib/Math/Strmanip.h"

namespace Hyphen
{
	int size(std::string input_str)
	{
		try
		{
			int i = 0;

			while (input_str[i] != '\0')
				i++;

			return i;
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	std::string char_to_string(const char * input)
	{
		try
		{
			int i = 0;
			std::string output = "";

			while (input[i] != '\0')
			{
				output += input[i];

				i++;
			}

			return output;
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	std::string char_to_string(char * input)
	{
		try
		{
			int i = 0;
			std::string output = "";

			while (input[i] != '\0')
			{
				output += input[i];

				i++;
			}

			return output;
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	Array<std::string> split(std::string arr, char c)
	{
		try
		{
			int size = 1;
			int i = 0;
			int j = 0;

			while (arr[i] != '\0')
			{
				if (arr[i] == c)
					size++;

				i++;
			}

			i = 0;
			std::string * aux = new std::string[size];

			while (arr[i] != '\0')
			{
				if (arr[i] != c)
					aux[j] += arr[i];
				else
				{
					if (aux[j] != "")
						j++;

					if (arr[i + 1] == '\0')
						j--;
				}

				i++;
			}

			return Array<std::string>(aux, j + 1);
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	std::string replace(std::string arr, std::string to_replace, std::string c)
	{
		try
		{
			std::string output = "";
			std::string aux_str = "";
			int i = 0, j = 0, k = 0, z = 0, aux_i = 0;
			bool start_replace = false;
			int to_replace_size;

			while (arr[i] != '\0')
			{
				aux_str = "";
				start_replace = false;

				if (arr[i] == to_replace[0])
				{
					aux_i = i;

					to_replace_size = size(to_replace);

					while (aux_i - i < to_replace_size)
					{
						if (arr[aux_i] != '\0')
							aux_str += arr[aux_i];
						else
						{
							aux_str = "";
							break;
						}

						aux_i++;
					}

					if (aux_str == to_replace)
					{
						i += to_replace_size - 1;
						aux_str = "";
						start_replace = true;
					}
				}

				if (!start_replace)
					output += arr[i];

				if (start_replace)
					output += c;

				i++;
			}

			return output;
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	std::string replace(std::string arr, std::string to_replace[], int len, std::string c)
	{
		try
		{
			std::string output = "";
			std::string aux_str = "";
			int i = 0, j = 0, k = 0, z = 0, aux_i = 0;
			bool start_replace = false;
			int to_replace_size;

			while (arr[i] != '\0')
			{
				while (z < len)
				{
					aux_str = "";
					start_replace = false;

					if (arr[i] == to_replace[z][0])
					{
						aux_i = i;

						to_replace_size = size(to_replace[z]);

						while (aux_i - i < to_replace_size)
						{
							if (arr[aux_i] != '\0')
								aux_str += arr[aux_i];
							else
							{
								aux_str = "";
								break;
							}

							aux_i++;
						}

						if (aux_str == to_replace[z])
						{
							i += to_replace_size - 1;
							aux_str = "";
							start_replace = true;

							break;
						}
					}

					z++;
				}

				if (!start_replace)
					output += arr[i];

				if (start_replace)
					output += c;

				i++;
				z = 0;
			}

			return output;
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	std::string replace(std::string arr, std::string to_replace[], int len, std::string c[])
	{
		try
		{
			std::string output = "";
			std::string aux_str = "";
			int i = 0, j = 0, k = 0, z = 0, aux_i = 0;
			bool start_replace = false;
			int to_replace_size;

			while (arr[i] != '\0')
			{
				while (z < len)
				{
					aux_str = "";
					start_replace = false;

					if (arr[i] == to_replace[z][0])
					{
						aux_i = i;

						to_replace_size = size(to_replace[z]);

						while (aux_i - i < to_replace_size)
						{
							if (arr[aux_i] != '\0')
								aux_str += arr[aux_i];
							else
							{
								aux_str = "";
								break;
							}

							aux_i++;
						}

						if (aux_str == to_replace[z])
						{
							i += to_replace_size - 1;
							aux_str = "";
							start_replace = true;

							break;
						}
					}

					z++;
				}

				if (!start_replace)
					output += arr[i];

				if (start_replace)
					output += c[z];

				i++;
				z = 0;
			}

			return output;
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	std::string replace_duplicate(std::string input_string, std::string to_replace, std::string replace_with)
	{
		try
		{
			int i = 0, j = 0, aux_i = 0;
			bool start_replace = false;
			std::string check_str = "";
			std::string output = "";

			while (input_string[i] != '\0')
			{
				start_replace = false;

				if (input_string[i] == to_replace[0])
					start_replace = true;

				if (start_replace)
				{
					aux_i = i;

					while (to_replace[j] != '\0')
					{
						if (input_string[aux_i] != '\0' && input_string[aux_i] == to_replace[j])
							check_str += to_replace[j];
						else
						{
							check_str = "";
							break;
						}

						aux_i++;
						j++;
					}
				}

				if (!start_replace || check_str == "")
					output += input_string[i];

				if (check_str != "")
				{
					if (input_string[i + 1] != to_replace[0])
						output += replace_with;

					check_str = "";
				}

				i++;
				j = 0;
			}

			return output;
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	std::string read(std::string str, bool * lookup, void(*handler)(std::string &),
		bool to_output, bool get_word, char ignore_char)
	{
		std::string output = "";
		std::ifstream fout;
		std::string word = "";
		short unsigned int print = 1;
		short unsigned int ignore = 0;
		bool duplicate = false;

		try
		{
			fout.open(str);

			if (fout.fail())
				throw std::exception(("Cannot open file with path: " + str).c_str());

			char c = fout.get();

			while (fout.good())
			{
				//Branchless if(c == ignore_char) then c = true else retain previous value
				ignore = (c == ignore_char) * !ignore;
				//Branchless if(c == '\n') then ignore = false else retain the previous value
				ignore = !(c == '\n') * ignore;

				if (lookup && lookup[c] && !duplicate)
				{
					print = 1;
					duplicate = true;
				}

				if (!ignore && get_word && (lookup && lookup[c] || c == '\n'))
				{
					if (print)
					{
						handler(word);
						print = 0;
					}
					word = "";
				}
				else if (!ignore && get_word)
				{
					word += c;
					duplicate = false;
				}

				output += (to_output) * c;
				c = fout.get();
			}
			fout.close();
			return output;
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);
			std::cerr << e.what() << std::endl;
			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	std::string read(std::string str, std::string bookmark, int bookmark_no, char eol)
	{
		std::string output_check = "";
		std::string output = "";
		std::ifstream fout;

		try
		{
			int bookmark_i = 0;
			fout.open(str);

			if (fout.fail())
				throw std::exception(("Cannot open file with path: " + str).c_str());

			char c = fout.get();

		while_loop:
			while (fout.good())
			{
				output_check += c;

				if (output_check == bookmark)
					bookmark_i++;

				if (bookmark_i < bookmark_no)
				{
					fout.ignore(999999999, eol);
					output_check = "";
				}

				if (bookmark_i == bookmark_no)
				{
					c = fout.get();

					if (c == '\n')
					{
						output_check = "";
						c = fout.get();
					}
					else
						output += c;

					goto while_loop;
				}

				if (bookmark_i > bookmark_no)
					break;

				c = fout.get();
			}

			fout.close();

			return output;
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	void write(std::string file, std::string output, std::string mode, bool newline)
	{
		try
		{
			std::ofstream fin;
			fin.open(file, (mode == "trunc" ? std::fstream::trunc : (mode == "app" ? std::fstream::app : std::fstream::out)));

			fin << output << (newline == true ? "\n" : "");

			fin.close();
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}

	int grep(std::string str, std::string key)
	{
		try
		{
			int i = 0;
			int j = 0;
			bool check = false;
			int response = 0;

			while (str[i] != '\0')
			{
				if (str[i] == key[j])
				{
					check = true;
				}
				else
					if (key[j] != '\0')
					{
						check = false;
						j = 0;
					}

				i++;
				if (check && key[j] != '\0')
					j++;

				if (str[i] == '\0' && key[j] != '\0')
					response = 0;

				if (str[i] == '\0' && key[j] == '\0' && check)
					response = 1;
			}

			return response;
		}
		catch (const std::exception& e)
		{
			std::string file_name(__FILE__);

			throw std::runtime_error("EXCEPTION IN FILE: " + file_name + ", THROWN ON LINE: " + std::to_string(__LINE__) + "\n\t\t" + e.what());
		}
	}
}