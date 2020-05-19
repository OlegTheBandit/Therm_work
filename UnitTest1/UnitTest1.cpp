#include "pch.h"
#include "CppUnitTest.h"
#include "..//Therm_work/Therm_work.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
		List<string> verties;
		ifstream file;
		int** test_matrix;
	private:



	public:

		TEST_METHOD(test_city_list_build)
		{

			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test.txt");
			city_list_build(verties, file);
			Assert::AreEqual(verties.get_pointer(0)->data, (string)"S");
			Assert::AreEqual(verties.get_pointer(1)->data, (string)"B");
			Assert::AreEqual(verties.get_pointer(2)->data, (string)"C");
			Assert::AreEqual(verties.get_pointer(3)->data, (string)"T");
			file.close();

		}
		TEST_METHOD(test_matrix_build)
		{
			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test.txt");
			city_list_build(verties, file);
			file.close();
			test_matrix = new int* [verties.get_size()];
			for (int i = 0; i < verties.get_size(); i++)
			{
				test_matrix[i] = new int[verties.get_size()];
			}
			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test.txt");
			matrix_build(verties, file, test_matrix);
			Assert::AreEqual(test_matrix[0][1], 1000);
			Assert::AreEqual(test_matrix[0][2], 1000);
			Assert::AreEqual(test_matrix[0][1], 1000);
			Assert::AreEqual(test_matrix[1][2], 1);
			Assert::AreEqual(test_matrix[1][3], 1000);
			Assert::AreEqual(test_matrix[2][3], 1000);
			file.close();
		}
		
		TEST_METHOD(test_TrueTransport_network)
		{
			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test.txt");


			city_list_build(verties, file);
			file.close();
			test_matrix = new int* [verties.get_size()];

			for (int i = 0; i < verties.get_size(); i++)
			{
				test_matrix[i] = new int[verties.get_size()];
			}
			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test.txt");
			matrix_build(verties, file, test_matrix);

			Assert::IsTrue(TrueTransport_network(test_matrix, verties));

			
		}
		TEST_METHOD(test_TrueTransport_network_false)
		{
			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test_wrong.txt");


			city_list_build(verties, file);
			file.close();
			test_matrix = new int* [verties.get_size()];

			for (int i = 0; i < verties.get_size(); i++)
			{
				test_matrix[i] = new int[verties.get_size()];
			}
			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test_wrong.txt");
			matrix_build(verties, file, test_matrix);

			Assert::IsFalse(TrueTransport_network(test_matrix, verties));


		}
		TEST_METHOD(test_dfs)
		{
			
			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test.txt");
		
			
			city_list_build(verties, file);
			file.close();
			test_matrix = new int* [verties.get_size()];
			
			for (int i = 0; i < verties.get_size(); i++)
			{
				test_matrix[i] = new int[verties.get_size()];
			}
			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test.txt");
			matrix_build(verties, file, test_matrix);

			int source, target;
			for (int i = 0; i < verties.get_size(); i++)
			{
				if (verties.get_pointer(i)->data == "S")
					source = i;
				if (verties.get_pointer(i)->data == "T")
					target = i;
			}

			List<bool> marks;
			for (int i = 0; i < verties.get_size(); i++)
			{
				marks.push_back(0);
			}
			int delta;
			int flow = 0;
			for (int i = 0; i < verties.get_size(); i++)
			{
				for (int j = 0; j < verties.get_size(); j++)
				{

					if (test_matrix[i][j] < 0)
					{
						test_matrix[i][j] = 0;
					}
				}
			}
			while (1)
			{
				fild(marks);
				delta = dfs(test_matrix, source, 9999999, marks, verties, flow);
				cout << delta;
				cout << endl;
				if (delta > 0)
					flow += delta;

				else
					break;
			}
			Assert::AreEqual(flow, 2000);
		}
		TEST_METHOD(test_dfs_1)
		{

			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test1.txt");


			city_list_build(verties, file);
			file.close();
			test_matrix = new int* [verties.get_size()];

			for (int i = 0; i < verties.get_size(); i++)
			{
				test_matrix[i] = new int[verties.get_size()];
			}
			file.open("D:\\Aistr\\4th term\\Therm_work\\UnitTest1\\test1.txt");
			matrix_build(verties, file, test_matrix);

			int source, target;
			for (int i = 0; i < verties.get_size(); i++)
			{
				if (verties.get_pointer(i)->data == "S")
					source = i;
				if (verties.get_pointer(i)->data == "T")
					target = i;
			}

			List<bool> marks;
			for (int i = 0; i < verties.get_size(); i++)
			{
				marks.push_back(0);
			}
			int delta;
			int flow = 0;
			for (int i = 0; i < verties.get_size(); i++)
			{
				for (int j = 0; j < verties.get_size(); j++)
				{

					if (test_matrix[i][j] < 0)
					{
						test_matrix[i][j] = 0;
					}
				}
			}
			while (1)
			{
				fild(marks);
				delta = dfs(test_matrix, source, 9999999, marks, verties, flow);
				cout << delta;
				cout << endl;
				if (delta > 0)
					flow += delta;

				else
					break;
			}
			Assert::AreEqual(flow, 5);
		}

		TEST_METHOD(test_fild)
		{
			List<bool> testing_list;
			for (int i = 0; i < 10; i++)
			{
				testing_list.push_back(1);
			}
			fild(testing_list);
			for (int i = 0; i < 10; i++)
			{
				Assert::IsFalse(testing_list.get_pointer(i)->data);
			}
		}
	};
}
