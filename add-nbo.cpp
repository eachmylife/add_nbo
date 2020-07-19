#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <netinet/in.h>

void printsum(int* arr1, int* arr2) {
	uint8_t buf[4];			//매개변수로 받아온 arr를 uint8_t로 변환하기 위한 버퍼를 선언한다.
	for (int i=0 ; i<sizeof(buf) ; i++) {
		buf[i] = arr1[i];		//buf에 arr1값을 담는다
	}
	uint32_t* p = reinterpret_cast<uint32_t*>(buf);
	uint32_t n1 = ntohl(*p);		//ntohl()함수는 네트워크 바이트 오더를 호스트 바이트 오더로 변환하는데 
						//컴파일러가 빅엔디안인지 리틀엔디안인지를 알.아.서 파악하기 때문에 그냥 사용하면 된다.
	for (int i=0 ; i<sizeof(buf) ; i++) {
		buf[i] = arr2[i];
	}
	p = reinterpret_cast<uint32_t*>(buf);
	uint32_t n2 = ntohl(*p);
	
	printf("%d(0x%08x) + %d(0x%08x) = %d(0x%08x)\n", n1, n1, n2, n2, n1+n2, n1+n2);	//합계를 출력

}


int main(int argc, char** argv) {

	int num1, num2;		//파일에서 1바이트씩 읽어온 값을 받을 임시변수 num1, num2
	int arr1[4], arr2[4];	//임시변수 num1,2가 받은 1바이트의 정수를 저장할 배열(크기는 4로 하드코딩)
	FILE *fp1 = fopen(argv[1], "r");	//파일포인터를 선언하고 첫번째 파라미터와
	FILE *fp2 = fopen(argv[2], "r");	//두번째 파라미터를 읽기모드로 오픈함
	
	int i = 0, j = 0;
	while ( (num1 = fgetc(fp1)) != EOF ) {	//fgetc함수를 통해 EOF가 아닌동안 1바이트씩 값을 읽어와서 정수로 리턴
		arr1[i++] = num1;		//num1 임시변수가 받은 값을 배열에 저장
	}
	while ( (num2 = fgetc(fp2)) != EOF ) {
		arr2[j++] = num2;
	}
	
	printsum(arr1, arr2);		//합계함수 호출
	
	fclose(fp1);
	fclose(fp2);
}
