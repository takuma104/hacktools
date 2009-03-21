void func1()
{
}

void func2()
{
	func1();
}

void func3()
{
	func2();
}

void func4()
{
	func2();
	func3();
}

int main(int argc, char *argv[])
{	
	func3();
	func4();
	func2();
	return 0;
}

