﻿#pragma once

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <string>
#include <cstdlib>

#include "SortedList.h"
#include "Queue.h"

#include "FolderType.h"
#include "Frequent.h"

#include "Windows.h"

using namespace std;

/**
*	application class for folder management simply.
*/
class Application {
private:
	FolderType m_RootFolder;
	FolderType *m_CurFolder;
	SortedList<FolderType> *m_CopyFolder = new SortedList<FolderType>();
	SortedList<FolderType> *m_CutFolder = new SortedList<FolderType>();
	SortedList<FileType> *m_CopyFile = new SortedList<FileType>();
	SortedList<FileType> *m_CutFile = new SortedList<FileType>();
	Queue<FolderType> m_RecentFolder;
	Queue<FileType> m_RecentFile;
	Queue<FolderType> m_FavoriteFolder;
	Queue<FileType> m_FavoriteFile;
	Frequent<FolderType> m_FrequentFolder;
	Frequent<FileType> m_FrequentFile;
	int m_Command;
	
public:
	/**
	*	default constructor with folder name.
	*/
	Application(string folderName = "root", string folderLocation = ".\\") {
		m_Command = 0;
		
		// main에서 root folder를 application class를 정의하고 제어를 root folder의 Run함수로 넘긴다
		m_RootFolder.SetName(folderName);
		m_RootFolder.SetLocation(folderLocation);
		m_RootFolder.SetCreateDateToNow();
		m_RootFolder.SetModifyDateToNow();
		m_RootFolder.SetAccessDateToNow();
		m_RootFolder.SetFolderNumber(0);
		m_RootFolder.SetFileNumber(0);
		m_RootFolder.SetSubFolderList(new SortedList<FolderType>);
		m_RootFolder.SetFileList(new SortedList<FileType>);

		m_CurFolder = &m_RootFolder;
		m_RecentFolder.EnQueue(*m_CurFolder);

		Windows::CreateDirectoryWithPath(".\\root");
	}

	/**
	*	destructor.
	*/
	~Application() {
		delete m_CopyFolder;
		delete m_CopyFile;
		delete m_CutFolder;
		delete m_CutFile;
	}

	/**
	*	@brief	어플리케이션 실행
	*/
	void Run();

	/**
	*	@brief	실행에 필요한 명령을 받아옴. (폴더)
	*	@pre	명령어 목록을 출력한다.
	*	@post	명령을 입력받는다.
	*	@return	해당 명령어 숫자 리턴
	*/
	int GetFolderCommand();

	/**
	*	@brief	실행에 필요한 명령을 받아옴. (파일)
	*	@pre	명령어 목록을 출력한다.
	*	@post	명령을 입력받는다.
	*	@return	해당 명령어 숫자 리턴
	*/
	int GetFileCommand();

	/**
	*	@brief	실행에 필요한 명령을 받아옴. (탐색기)
	*	@pre	명령어 목록을 출력한다.
	*	@post	명령을 입력받는다.
	*	@return	해당 명령어 숫자 리턴
	*/
	int GetExplorerCommand();

	/**
	*	@brief	새로운 폴더를 생성한다.
	*	@pre	폴더 정보가 필요함.
	*	@post	새로운 폴더가 생성됨.
	*/
	void NewFolder();

	/**
	*	@brief	폴더명을 기준으로 삭제한다.
	*	@pre	폴더명이 필요함.
	*	@post	폴더가 삭제됨.
	*/
	void DeleteFolder();

	/**
	*	@brief	폴더명을 변경한다.
	*	@pre	폴더명이 필요함.
	*	@post	폴더명이 변경됨.
	*/
	void RenameFolder();

	/**
	*	@brief	서브 폴더를 연다.
	*	@pre	서브 폴더가 존재해야됨.
	*	@post	서브 폴더로 이동.
	*/
	void OpenFolder();

	/**
	*	@brief	좋아하는 폴더로 등록한다.
	*	@post	성공했다면 등록완료 출력.
	*/
	void SetAsFavoriteFolder();

	/**
	*	@brief	최근 열어본 폴더를 출력한다.
	*	@post	폴더 정보를 받아옴.
	*	@post	목록이 차례대로 출력된다.
	*/
	void DisplayRecentFolder();

	/**
	*	@brief	좋아하는 폴더를 출력한다.
	*	@post	폴더 정보를 받아옴.
	*	@post	목록이 차례대로 출력된다.
	*/
	void DisplayFavoriteFolder();

	/**
	*	@brief	자주 사용했던 폴더를 출력한다.
	*	@post	폴더 정보를 받아옴.
	*	@post	목록이 차례대로 출력된다.
	*/
	void DisplayFrequentFolder();

	/**
	*	@brief	루트 폴더의 정보와 서브 폴더, 파일의 정보를 출력한다.
	*	@post	정보가 출력됨.
	*/
	void DisplayProperty();

	/**
	*	@brief	상위 폴더로 이동함.
	*	@pre	상위 폴더가 있어야 됨.
	*	@post	상위 폴더로 이동함, 루트 폴더면 이동하지 않는다.
	*/
	void MoveToParentFolder();

	/**
	*	@brief	하위의 서브폴더 위치 값을 모두 갱신해준다.
	*	@pre	갱신되지 않은 서브폴더 리스트가 주어짐.
	*	@post	위치 정보가 갱신됨.
	*	@param	list:		FolderType 변수
	*	@param	location:	갱신할 위치 문자열
	*/
	void RecursiveUpdateLocation(FolderType *list, string location);

	/**
	*	@brief	폴더를 복사함.
	*	@pre	현재 폴더를 복사한다.
	*	@post	변수에 현재 폴더 주소값이 저장됨.
	*/
	void CopyFolder();

	/**
	*	@brief	폴더를 자르기함.
	*	@pre	현재 폴더를 자른다.
	*	@post	변수에 현재 폴더 주소값이 저장됨.
	*/
	void CutFolder();

	/**
	*	@brief	복사한 폴더를 붙여넣기함.
	*	@pre	변수에 폴더 주소값이 지정되어있어야 함.
	*	@post	현재 폴더 위치에 붙여넣고, 변수를 초기화함.
	*/
	void PasteCopyFolder();

	/**
	*	@brief	잘라내기한 폴더를 붙여넣기함.
	*	@pre	변수에 폴더 주소값이 지정되어있어야 함.
	*	@post	현재 폴더 위치에 붙여넣고, 변수를 초기화함.
	*/
	void PasteCutFolder();

	/**
	*	@brief	폴더를 붙여넣기함.
	*	@pre	변수에 폴더 주소값이 지정되어있어야 함.
	*	@post	현재 폴더 위치에 붙여넣고, 변수를 초기화함.
	*/
	void PasteFolder();
	
	/**
	*	@brief	새로운 파일을 생성한다.
	*	@pre	파일 정보가 필요함.
	*	@post	새로운 파일이 생성됨.
	*/
	void NewFile();

	/**
	*	@brief	파일명을 기준으로 삭제한다.
	*	@pre	파일명이 필요함.
	*	@post	파일이 삭제됨.
	*/
	void DeleteFileA();

	/**
	*	@brief	파일 속성을 변경한다.
	*	@pre	파일이 존재해야 됨.
	*	@post	파일이 변경됨.
	*/
	void RenameFile();

	/**
	*	@brief	파일을 연다.
	*	@pre	파일이 존재해야 됨.
	*	@post	파일을 수정할 수 있다.
	*/
	void OpenFile();

	/**
	*	@brief	좋아하는 파일로 등록한다.
	*	@post	성공했다면 등록완료 출력.
	*/
	void SetAsFavoriteFile();

	/**
	*	@brief	파일을 복사함.
	*	@pre	현재 파일을 복사한다.
	*	@post	변수에 현재 폴더 주소값이 저장됨.
	*/
	void CopyFileA();

	/**
	*	@brief	파일을 자르기함.
	*	@pre	현재 파일을 자른다.
	*	@post	변수에 현재 폴더 주소값이 저장됨.
	*/
	void CutFile();

	/**
	*	@brief	복사한 파일을 붙여넣기함.
	*	@pre	변수에 파일 주소값이 지정되어있어야 함.
	*	@post	현재 폴더 위치에 붙여넣고, 변수를 초기화함.
	*/
	void PasteCopyFile();

	/**
	*	@brief	잘라내기한 파일을 붙여넣기함.
	*	@pre	변수에 파일 주소값이 지정되어있어야 함.
	*	@post	현재 폴더 위치에 붙여넣고, 변수를 초기화함.
	*/
	void PasteCutFile();

	/**
	*	@brief	파일을 붙여넣기함.
	*	@pre	변수에 파일 주소값이 지정되어있어야 함.
	*	@post	현재 폴더 위치에 붙여넣고, 변수를 초기화함.
	*/
	void PasteFile();

	/**
	*	@brief	파일 및 폴더를 검색한다.
	*	@pre	이름이 입력되어야 함.
	*	@post	모든 검색결과를 출력한다.
	*/
	void Search();

	/**
	*	@brief	재귀 검색한다.
	*	@pre	폴더 위치와 이름이 입력되야 함.
	*	@post	모든 검색결과를 출력한다.
	*	@param	f:	FolderType
	*	@param	w:	Search string
	*/
	void RecursiveSearch(FolderType* f, string w);

	/**
	*	@brief	최근 열어본 파일 목록을 출력한다.
	*	@post	파일 정보를 받아옴.
	*	@post	목록이 차례대로 출력된다.
	*/
	void DisplayRecentFile();

	/**
	*	@brief	좋아하는 파일을 출력한다.
	*	@post	파일 정보를 받아옴.
	*	@post	목록이 차례대로 출력된다.
	*/
	void DisplayFavoriteFile();

	/**
	*	@brief	자주 사용했던 파일을 출력한다.
	*	@post	파일 정보를 받아옴.
	*	@post	목록이 차례대로 출력된다.
	*/
	void DisplayFrequentFile();

	/**
	*	@brief	최근에 열어본 폴더 및 파일을 출력한다.
	*	@post	폴더 및 파일 정보를 받아옴.
	*	@post	목록이 차례대로 출력된다.
	*/
	void DisplayRecent();

	/**
	*	@brief	좋아하는 폴더 및 파일을 출력한다.
	*	@pre	좋아하는 폴더 및 파일 목록이 있어야 함.
	*	@post	목록이 차례대로 출력된다.
	*/
	void DisplayFavorite();

	/**
	*	@brief	자주 사용했던 폴더 및 파일을 출력한다.
	*	@pre	자주 사용했던 폴더 및 파일 목록이 있어야 함.
	*	@post	목록이 차례대로 출력된다.
	*/
	void DisplayFrequent();

	/**
	*	@brief	root 폴더로부터 파일 시스템 구조를 불러온다.
	*	@pre	root 폴더가 존재해야 함.
	*	@post	파일 시스템 구조가 정상적으로 읽어짐.
	*/
	void ReadDataFromSystem();
};
#endif //_APPLICATION_H