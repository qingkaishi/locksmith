void (*fptr)(int*);
int* f(int *m) {
	*m = 10;
	return m;
}
int main() {
	int j = 0;
	int *k = &j;
	fptr = &f;
	fptr(&j);
	return *k;
}
