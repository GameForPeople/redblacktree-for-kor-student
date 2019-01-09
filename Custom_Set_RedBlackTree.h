#pragma once

/*
	Custom_Set_RedBlackTree		

		�ϳ��� Ŭ������ ���� �ϴ� �����Ʈ�� ( ���泪�� ? ) �ڵ��Դϴ�.
		���θ� ���� �����Ҹ��� ���� �� Ʈ�� �ڵ带 ã�� �߿�, ������ �ڵ尡 ���.... xtree...�̰� ���� C++�� �ۼ��Ȱ� �´���...
		
		���л� 3�г� ��� ���ؿ��� ������ �� �ֵ��� ���������� ������, 
		�� �ѱ���� �ּ��� �ۼ��Ͽ� ���ݴ� ģ����, 
		�����Ʈ�� �ڵ� �ۼ��� ��ǥ�� �߽��ϴ�. 
			
		��� ���� ���л��̶�...�� �ɷº������� ����.. �и��� ������ �� �� �ִ� �κ��� ���ƿ�.. ���������� ������ ���, PR��Ź�����!
	
	#0. ���� �Լ��� �����մϴ�. CUSTOM_SET::TestFunc()�� main�� �־��ּſ�!
	#1. ����Լ��� ������� �ʴ� Ʈ�� ��ȸ �Լ��� �������� �߰�....��	
	#2. �����Ʈ���� ���� �̷����� ������ ��Ű��� (https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC)�� Ȯ���ϼ���!

	!0. ���� ���� ��, ��Ƽ ����Ʈ�� SDL �˻��� Off, C++17 ���� ��� ���� Ȯ�����ּ���!
	!1. �翬�� ���� ��� ���� �ʽ��ϴ�... c++17�� �߰��� parallel stl ������..! ���� ���༺ �ʿ� ���... Set, Map ������!! STL ¯¯!
	!2. ���ø� DATA, KEY_TYPE�� ���Ͽ�.. �ɷº������� ���� �Ϻ� �䱸������ �����մϴ�! rbTreeNode�� �ּ��� Ȯ�����ּ��� :)

	������ �ڵ带 Ȯ�����ּż� �����մϴ� :)

	2019�� 1�� 3�� 
	������ �ø�.
	KoreaGameMaker@gmail.com
	GameForPeople(github)
*/

// stdafx.h
// #include <iostream>
#define		INLINE				__inline
#define		_NODISCARD			[[nodiscard]]
#define		_DEPRECATED			[[deprecated]]
#define		DEBUG_TEST_FUNC		/* Test Func Region */ 

namespace CUSTOM_SET_REDBLACKTREE
{
#pragma region [ Declare rbTreeNode, rbTree ]

	template <typename DATA, typename KEY_TYPE>
	class rbTree;

	template <typename DATA, typename KEY_TYPE>
	class rbTreeNode;

	/*
		rbTreeNode
			- rbTree�� �����ϴ� ����(Node)�Դϴ�.

		#0. DATA�� ������ ������, KEY_TYPE�� GetKey()�� ��ȯ�Ǵ� �ڷ����Դϴ�.

		!0. DATA�� �ǹ������� GetKey() �Լ��� �����ؾ��մϴ�.
		!1. KEY_TYPE�� ���� �ڷ����� �ƴ� ��� �Ϻ� �����ڸ� �䱸�մϴ�. (TestKey Class�� �������ּ���!)
			- Ű �� ũ�� �񱳿� ���� ������ operator<()�� ����(�����ε�)�ؾ��մϴ�.
			- Ű ���� �������� �˻��Ҷ� ���� ������ operator==()�� ����(�����ε�)�ؾ��մϴ�.
			- ��¿� ���� ������ operator<<()�� ����(�����ε�)�ؾ��մϴ�.
		
		!2. DATA�� KEY_TYPE�� �⺻ �����ڸ� �䱸�մϴ�.
			- rbTree�� pNullNode(NIL)�� �����ϴµ�, �̶� ���� �⺻�����ڸ� �䱸�մϴ�.
	*/
	template <typename DATA, typename KEY_TYPE>
	class rbTreeNode {
		friend class rbTree<DATA, KEY_TYPE>;

		// Define Color RED = true, BLACK = false;
		enum : bool
		{
				RED		= true	//TRUE
			,	BLACK	= false	//FALSE
		};

	private:
		DATA							data;	// data

		bool							color;	// false ( 0 ) == black, true (1) == red;


		rbTreeNode<DATA, KEY_TYPE>*		up;		// Parent Node Pointer
		rbTreeNode<DATA, KEY_TYPE>*		left;	// Left Child Node Pointer
		rbTreeNode<DATA, KEY_TYPE>*		right;	// Right Child Node Pointer

	public:
		/*
			Define the constructor for pNullNode.
				#0. rbTree���� nullNode�� Ȱ���ϱ⿡ �̸� �������ֱ� ���� �⺻�����ڰ� �ʿ��մϴ�.
		*/ 
		rbTreeNode<DATA, KEY_TYPE>() noexcept
			: data(), up(this), left(this), right(this), color(false)
		{}

		/* 
			Define the constructor for Insert 1
		*/
		rbTreeNode<DATA, KEY_TYPE>(const DATA& InDATA) noexcept
			: data(InDATA), up(nullptr), left(nullptr), right(nullptr), color(false)
		{}

		/*
			Define the constructor for Insert 2
		*/
		rbTreeNode<DATA, KEY_TYPE>(const DATA& InDATA, rbTreeNode<DATA, KEY_TYPE>* pInNode, const bool InColor)
			: data(InDATA), up(pInNode), left(pInNode), right(pInNode), color(InColor)
		{}

		/* Define the destructor.(default)*/ 
		~rbTreeNode<DATA, KEY_TYPE>() = default;

	public:
		/*
			GetKey()
				- data ��ü���� ���ǵ� GetKey()�� ȣ��, ��ȯ�մϴ�.

			!0. data�� ��ȯ�մϴ�.
		*/
		_NODISCARD INLINE DATA	GetData() const noexcept { return data; };

		/*
			GetKey()
				- data ��ü���� ���ǵ� GetKey()�� ȣ��, ��ȯ�մϴ�.

			!0. data�� ���� ��ü���� �ش� �Լ� (GetKey)�� �־�� �մϴ�.
		*/
		_NODISCARD INLINE KEY_TYPE	GetKey() const /*noexcept*/ { return data.GetKey(); };

	public:
		/*
			PrintNodeInfo()
				- ����� ����, ��, ����, 

			!0. ���� ���� ��¹��� ���Ե� ������ ������� ���� ���� �Լ� �Դϴ�.
		*/
		_DEPRECATED void PrintNodeInfo(rbTreeNode<DATA, KEY_TYPE>* pNullNode) noexcept
		{
			std::cout << "       ";

			std::cout << GetKey() << ' ';

			std::cout << "    ";

			if (color == RED)
				std::cout << "RED   ";
			else
				std::cout << "BLACK ";

			std::cout << "     ";

			if (up != pNullNode)
				std::cout << up->GetKey() << ' ';
			else
				std::cout << "NULL ";

			std::cout << "     ";

			if (left != pNullNode)
				std::cout << left->GetKey() << ' ';
			else
				std::cout << "NULL ";

			std::cout << "     ";

			if (right != pNullNode)
				std::cout << right->GetKey() << ' ';
			else
				std::cout << "NULL ";

			std::cout << "\n";
		}
	};

	/*
		rbTree
			- rbTreeNode�� ������ �����Ʈ���Դϴ�.

		#0. DATA�� ������ ������, KEY_TYPE�� GetKey()�� �ڷ����Դϴ�.
		#1. pNullNode�� ����մϴ�. ( = NIL)

		!0. rbTreeNode�� rbTreeNode�� ���ǻ����� �����ؾ��մϴ�.
	*/
	template <typename DATA, typename KEY_TYPE>
	class rbTree
	{
		using _Node = rbTreeNode<DATA, KEY_TYPE>;
		// Define Color RED = true, BLACK = false;
		enum : bool
		{
				RED		= true	//TRUE
			,	BLACK	= false	//FALSE
		};

		_Node*			pNullNode;	// NullNode's Color is Black. == same nil
		_Node*			pRoot;		// Root!

	public:
		rbTree<DATA, KEY_TYPE>() noexcept
			: pNullNode(new rbTreeNode<DATA, KEY_TYPE>()), pRoot(pNullNode)
		{
			/* �Ʒ�, �ڵ����, rbTreeNode::rbTreeNode()�� �����ڿ��� ����˴ϴ�.  In Node Construct rbTreeNode::rbTreeNode()
				pRoot = pNullNode;
				pNullNode->up = 0;
				pNullNode->left = 0;
				pNullNode->right = 0;
				pNullNode->color = BLACK;
			*/
		};

		/*
			!0. �� ������ �Ҹ��ڿ����� pRoot, pNullNode�� �����ϰ�� delete�� �������� �ʽ��ϴ�.
		*/
		~rbTree<DATA, KEY_TYPE>()
		{
			/*if (pRoot != nullptr) */
				delete pRoot;

			/*if (pNullNode != nullptr) */
				delete pNullNode;
		};

	public:
		_NODISCARD DATA					Search(const KEY_TYPE& InKey, bool& RetResult) const;		// �ش� Key������ �˻��Ͽ�, True�� ��� ������ ����, False�� ����(pNullNode Return). 
		void							Insert(const DATA& InDATA);									// �ش� key����, Value ���� ������, ���ο��� �Ҵ��Ͽ� Ʈ���� ���� ��, �ش� ��忡 ���� ������ ����.
		void							Delete(_Node* pDeletedNode);								// ���ڷ� ���޵� ����� �����͸� ����, �ش� ��带 �������ݴϴ�.
		bool							DeleteWithSearch(const KEY_TYPE& InKey);					// �ش� Ű�� �ش��ϴ� ��带 ã�� �������ݴϴ�.

	private:
		void							_ChangeForInsert(_Node* RetNode);
		void							_ChangeForDelete(_Node* RetNode);

		void							_LeftRotate(_Node* RetNode);
		void							_RightRotate(_Node* RetNode);

		_NODISCARD INLINE _Node*		_GetPrevNode(_Node* const InNode);
		_NODISCARD INLINE _Node*		_GetNextNode(_Node* const InNode);

		_NODISCARD INLINE _Node*		_GetSiblingNode(_Node* const InNode);
		_NODISCARD INLINE _Node*		_GetUncleNode(_Node* const InNode);

		//for Debug
	public:
		_DEPRECATED void				PrintTree();

	private:
		_DEPRECATED void				_PrintNodes(_Node* pNodeBuffer);
	};

#pragma endregion

#pragma region [ Definition of Functions ]

	// ================================== Search

	/*
		Search(const KEY_TYPE& InKey, bool& RetResult) 
			- �־��� Ű ���� ������, Ʈ������ �ش� Ű ���� ���� ��带 ã�� ����� �����͸� ��ȯ

		���� : Ž���Ϸ��� ����� Ű ��, Ž�� ���� ����
		��� : ������(���ϰ�), Ž�� ���� ����(����)

		!0. RetResult�� false�� ��, ����ó���� �ʿ��մϴ�.
	*/

	template <typename DATA, typename KEY_TYPE>
	DATA rbTree<DATA, KEY_TYPE>::Search(const KEY_TYPE& InKey, bool& RetResult) const
	{
		// ���� Search ����� �������� ��.
		RetResult = false;

		// ������ �����͸� �����ϰ�, pRootNode�� ������.
		rbTreeNode<DATA, KEY_TYPE>*  pRetNodeBuffer = pRoot;

		// ������~~~
		while (true)
		{
			// ������ ��� ������ (�˻��ϴ� ���) �� pNullNode�϶� ( False ) 
			if (pRetNodeBuffer == pNullNode)
			{
				RetResult = false;
				return pRetNodeBuffer->GetData();	// �������ɼ� �����մϴ�. data�� �⺻�����ڿ� ���� ������ ������ ��ȯ
			}

			// ã�� Ű (�Լ� ����)�� ���� �˻��ϴ� ����� Ű�� ������ ��, (True)
			if (InKey == pRetNodeBuffer->GetKey())
			{
				RetResult = true;
				return pRetNodeBuffer->GetData();
			}

			// Ű �񱳸� ����, Left Or Right ���� (Ʈ�� ���������� Ž��)
			if (InKey < pRetNodeBuffer->GetKey())
				pRetNodeBuffer = pRetNodeBuffer->left;
			else
				pRetNodeBuffer = pRetNodeBuffer->right;
		}
	};


	// ================================== Insert

	/*
		Insert(const DATA& InDATA)
			- ���ڷ� �����Ǵ� �ش� �����͸� ������ ��带 ����� �����ϴ� �Լ�.
	
		���� : ����� Ű, ������
		��� : �ش� ��忡 ���� ������ ����.
		
		!0. ������ Ʈ���� �����ϴ� ��忡 ���� ������ Ű���� ���Ͽ� Insert�� ��û�� ���, ������ ������ �� �� �ֽ��ϴ�.
		!1. ���ο��� Node�� ���� �Ҵ�(new) �� �Ͼ�ϴ�... Insert�� Mutex�� Lock���� ������!
	*/

	template <typename DATA, typename KEY_TYPE>
	/* _Node* */ void rbTree<DATA, KEY_TYPE>::Insert(const DATA& InData)
	{
#pragma region [ ������ ��� �Ҵ� & �ʿ��� ������ ���� ���� ]

		// ������ ����� �����͸� �����ϰ�, �Ҵ����ݴϴ�. ( Key, Value�� ���� ���� (Node���� ������ ���ǵ�)
		rbTreeNode<DATA, KEY_TYPE>* pRetNode = new rbTreeNode<DATA, KEY_TYPE>(InData, pNullNode, RED);

		// �ʿ��� �����͵��� �����մϴ�.
		rbTreeNode<DATA, KEY_TYPE>* pTraversalNode = pRoot;			// ��ȸ������, ���� ����� ��ġ�� Ž���ϱ� ���� ��ȸ�ϴ� �������Դϴ�.
		rbTreeNode<DATA, KEY_TYPE>* pParentNode = pNullNode;		// �θ������, �θ� ��带 �����صα� ���� �������Դϴ�.

#pragma endregion
#pragma region [ �����ϴ� ����� �ڽĳ�� �� �� ���� ]
		/*
		������ ��� ��ó���Դϴ�. 
			1. �ڽ� ��, ��� pNullNode�� �������ݴϴ�. 
			2. ���� - ��Ʈ�� ��Ģ�� ����, ������ ����� ���� RED(TRUE)�� �������ݴϴ�.
			
			���� 1,2�� �ڵ�� �ۼ��ϸ� �Ʒ� 3�ٰ� �����ϸ�, 
			rbTreeNode�� �����ڿ��� ó�����ݴϴ�.
			
			pRetNode->left = pNullNode;
			pRetNode->right = pNullNode;
			pRetNode->color = RED;
		*/

#pragma endregion
#pragma region [ �����ϴ� ����� �θ��� ã�� ]
		
		/*
			���Ե� �� �ִ� �� �ڸ����� �̵��մϴ�.
			pTraversalNode
				- pRetNode�� ���Ե� �� �ִ� ��ġ(��Ȯ���� Ʈ���� ��������� �ڽ�)���� �̵��ϴ� ���-������ �Դϴ�.
			pParentNode
				- pNodeA�� ���� while�������� ��ġ( ���� pNodeA�� �θ� ��� ������) �Դϴ�.
		*/
		while (pTraversalNode != pNullNode)
		{
			//���� ��ġ�� pParentNode�� �����ϰ�, ���� ��ġ�� �̵��մϴ�.
			pParentNode = pTraversalNode;

			//Ű �񱳸� ����, ������ ����� ��ġ (Left Or Right)�� �����մϴ�. (Ʈ�� ���������� Ž��)
			if (pRetNode->GetKey() /* == InKey */ < pTraversalNode->GetKey())
				pTraversalNode = pTraversalNode->left;
			else
				pTraversalNode = pTraversalNode->right;
		}

		// �����ϴ� �������� up Point(�θ� ��� ��ġ)�� ����, pParentNode(���� ��� ������ - �θ� ��ġ)�� �־��ݴϴ�.
		pRetNode->up = pParentNode;
#pragma endregion
#pragma region [ �����ϴ� ����� ��ġ ���ϱ� ]

		// ���� �θ� ���(RetNode->up == oldBuffer)�� pNullNode�� ���, ������ ���� Ʈ���� pRoot��尡 �˴ϴ�.
		if (pParentNode == pNullNode)
		{
			pRoot = pRetNode;
		}
		else
		{
			// Ʈ���� ���� ��尡 �ƴ� ���, �θ� ���( pParentNode == pRetNode->up)�� Ű ���� ����, �θ� ��忡���� ��ġ (Left Or Right)�� ���� �� �������ݴϴ�.
			if (pRetNode->GetKey() < pParentNode->GetKey() /* ==  pRetNode->up->GetKey()	*/)
				pParentNode->left = pRetNode;
			else
				pParentNode->right = pRetNode;

			// ���� ����ߴ� ����Ʈ ����. ������ �߸����� ��� ����.
			pTraversalNode = pRetNode;

			// ���� ��, ���� ���θ� �˻��ϰ� ���� �ʿ� ó���� �ϴ� �Լ��Դϴ�. ( [Insert Case 1 ] ù �����϶��� �ʿ�����ϴ�.(���� if��, -- if (pParentNode == pNullNode) )
			_ChangeForInsert(pTraversalNode);
		}

#pragma endregion
#pragma region [ ��Ʈ ����� ������ ���� ]
		// ���� - ��Ʈ�� ��Ģ�� ����, � ��ȯ�� �Ͼ��, ���������� �������������� ��Ʈ ���� �׻� �������� �����ؾ��մϴ�.
		pRoot->color = BLACK;

		////(�����)���� �Ҷ�����, Ʈ���� ����մϴ�.
		//this->PrintTree();

		// ������ ��带 �������ݴϴ�. -> ������ �����ݴϴ�.
		// return pRetNode;
#pragma endregion
	};

	/*
		_ChangeForInsert(rbTreeNode<DATA, KEY_TYPE>* RetNode);
			- Insert �Լ� ���ο��� ���Ǹ�, ��带 Insert �ϴ� ���� �߿�, Red-Black Tree�� Ư¡�� �����ϱ� ���� �˻��ϸ�, �ʿ� �� ���� ó���� ���ִ� �Լ��Դϴ�.

		���� : Insert�� ����� ������
		��� : void
		
		#1. ���� �̷��� ��Ű ���, ����-�� Ʈ���� Ȯ���� �ּ���! https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC
	*/
	template <typename DATA, typename KEY_TYPE>
	void rbTree<DATA, KEY_TYPE>::_ChangeForInsert(_Node* pRetNode)
	{
	LIKE_RECURSION:

		// [Insert Case 2] �̹� ������ Ʈ����, ���� �� Ʈ���� ������ �����ϱ� ������, �θ��� ��尡 �������� ���, ����� �ʿ䰡 �����ϴ�. (-> ���� ��� ������ ���� ���忡�� �߻��մϴ�.)  // �ش� ������ Insert Case 1�� �����ϴ� �����Դϴ�.
		if (pRetNode->up->color == BLACK)
		{
			return;
		}

		rbTreeNode<DATA, KEY_TYPE>* pUncleNode = _GetUncleNode(pRetNode); // UncleNode Pointer  
		rbTreeNode<DATA, KEY_TYPE>* pGrandNode = pRetNode->up->up; // ���θ�(�պθ�) ��� --> nullptr�� ���� �������� �ʽ��ϴ�. ( [Insert Case 1 - 2] ���� �ɷ����ϴ�.)

		// [Insert Case 3] Recoloring - �θ���� UncleNode ��� �������� ��, �̸� ��� ���������� �ٲٰ�, ���θ��带 ���������� �����մϴ�. 
		if (pUncleNode->color == RED /*&& pUncleNode != pNullNode // �� ������ �������� ����. */)
		{
			pRetNode->up->color = BLACK;
			pUncleNode->color = BLACK;
			pGrandNode->color = RED;

			// �� ���θ��带 ���������� �����߱� ������, �̿� ���� �����ϰ� �����Ʈ�� ����(���� ���� �׽�Ʈ �����)�� ���� �˻簡 �ʿ���.
			//_ChangeForInsert(pGrandNode); // <- ����Լ��� ������� ���� ( �޸� ������� )

			// ��� �����͸� ���θ� ���� ���� ��, goto������ �Լ� ù°�ٷ� �̵�.
			pRetNode = pGrandNode;
			goto LIKE_RECURSION;
		}

		// [Insert Case 4] Restructuring - �θ���� �������̳�, UncleNode�� �������� ��, ��翡 ����. ���� ȸ���� ���� ( Insert Case 4�� ��ģ Ʈ���� ���� ���� ���°� �Ǹ� ��Ģ�� ���� Insert Case 5�� �ʼ��� ��ġ�� �˴ϴ�. )
		if ((pRetNode == pRetNode->up->right) && (pRetNode->up == pGrandNode->left))
		{
			_LeftRotate(pRetNode->up);
			//_NewLeftRotate(pRetNode->up);
			pRetNode = pRetNode->left;
		}
		else if ((pRetNode == pRetNode->up->left) && (pRetNode->up == pGrandNode->right)) {
			_RightRotate(pRetNode->up);
			//_NewRightRotate(pRetNode->up);
			pRetNode = pRetNode->right;
		}

		// [Insert Case 5] ������� ������ �������̾� �޷�
		pGrandNode = pRetNode->up->up;

		pRetNode->up->color = BLACK;
		pGrandNode->color = RED;

		if (pRetNode == pRetNode->up->left)
			_RightRotate(pGrandNode);
		else
			_LeftRotate(pGrandNode);
	};


	// ================================== Delete

	/*
		Delete(rbTreeNode<DATA, KEY_TYPE>* DeletedNode);
			- ���ڷ� �����Ǵ� ����� �����͸� Ȱ����, �ش� ��带 �����մϴ�!

		���� : �����Ϸ��� ����� ������
		��� : void

		#0. ���� ���� - ��Ʈ�� ��İ� ���� �ٸ� ���� Copy Value�� �ƴ϶�, Node ��ü�� �����ϴ� ���Դϴ�.
		( ���ο��� Node�� ���� ptr�� Ȱ���� ��, �̿� ���� ������ �����ϱ� ����.)

		!0. ���ο��� Node�� ���� �޸� ȸ��(delete) �� �Ͼ�ϴ�.

		?0. deleted�� ����� �����Ͱ� pNullNode�� ����Ű��, nullptr ���� ������ �������� ������?
	*/
	template <typename DATA, typename KEY_TYPE>
	void rbTree<DATA, KEY_TYPE>::Delete(_Node* pDeletedNode)
	{
		// �����Ϸ��� ��尡 pNullNode�� �ƴ��� Ȯ���մϴ�. (pNullNode �����ϸ� ���� Ŭ���ϴ�.)
		if (pDeletedNode == pNullNode)
		{
			return;
		}

		rbTreeNode<DATA, KEY_TYPE>* pBuffer = pNullNode;
		rbTreeNode<DATA, KEY_TYPE>* pChildBuffer = pNullNode;
		bool deletedNodeColor = BLACK;

		// �ڽ� ��� �� �˻�. --> �ΰ� �� �������.
		if (pDeletedNode->left != pNullNode && pDeletedNode->right != pNullNode)
		{
			pBuffer = _GetNextNode(pDeletedNode);
			pChildBuffer = pBuffer->right;

			// GetNextNode�� �ٷ�, ���� ���� �ڽ��� ���� �����ʿ�.
			if (pDeletedNode->right == pBuffer)
			{
				if (pChildBuffer == pNullNode)
				{
					pChildBuffer->up = pBuffer;
				}
			}
			else if (pChildBuffer != pNullNode)
			{
				pChildBuffer->up = pBuffer->up;
				pBuffer->up->left = pChildBuffer;
			}
			else
			{
				// TEST ------------------------
				pChildBuffer->up = pBuffer->up;
				// TEST ------------------------

				pBuffer->up->left = pNullNode;
			}

			// NextNode�� ������, pDeletedBuffer�� ��������. (���� �����ϴ� ���� pBuffer�̱� ������) --> [DEV_55] (bug_3) nullptr ���� ���� �߻�.
			// Data Copy
			//pDeletedNode->key = pBuffer->key;
			//pDeletedNode->value = pBuffer->value;

			// (!Data) Copy
			// ���� Data Copy �ÿ���, ���� �ش� pBuffer�� ptr�� �ش��ϴ� ��带 �����ͷ� �����ϰ� Ȱ���ϴ� ������ ������ nullptr�� �Ͼ ��찡 �ֱ� ������ nodeSwap�� ����.
			if (pDeletedNode->up == pNullNode)
			{
				pRoot = pBuffer;
			}
			else
			{
				if (pDeletedNode->up->left == pDeletedNode)
					pDeletedNode->up->left = pBuffer;
				else
					pDeletedNode->up->right = pBuffer;
			}

			// �����ϴ� ����� �θ�� ����
			pBuffer->up = pDeletedNode->up;

			// �����ϴ� ����� �ڽĵ�� ����.
			pDeletedNode->left->up = pBuffer;
			pBuffer->left = pDeletedNode->left;

			// GetNextNode�� �ٷ�, ���� ���� �ڽ��� ���� �����ʿ�.
			if (pDeletedNode->right != pBuffer)
			{
				pDeletedNode->right->up = pBuffer;
				pBuffer->right = pDeletedNode->right;
			}

			// �÷� ���� ����.
			deletedNodeColor = pBuffer->color;
			pBuffer->color = pDeletedNode->color;
		}
		// �ڽ��� ���� ��常 �������.
		else if (pDeletedNode->left != pNullNode)
		{
			pBuffer = pDeletedNode;
			pChildBuffer = pBuffer->left;

			// �ڽĿ��� �� �θ� �˸�.
			pChildBuffer->up = pBuffer->up;

			// �����Ǵ� ��尡 root���� ���, ChildBuffer �� �ڽ��� �ǵ��� ��.
			if (pBuffer->up == pNullNode)
				pRoot = pChildBuffer;
			else
			{
				// pBuffer�� �θ𿡰�, �� �ڽ��� �˷���.
				if (pBuffer->up->left == pBuffer)
					pBuffer->up->left = pChildBuffer;
				else
					pBuffer->up->right = pChildBuffer;
			}
			// �� ����
			deletedNodeColor = pBuffer->color;
		}
		// �ڽ��� ������ ��常 �������.
		else if (pDeletedNode->right != pNullNode)
		{
			pBuffer = pDeletedNode;
			pChildBuffer = pBuffer->right;

			pChildBuffer->up = pBuffer->up;

			if (pBuffer->up == pNullNode)
				pRoot = pChildBuffer;
			else
			{
				if (pBuffer->up->left == pBuffer)
					pBuffer->up->left = pChildBuffer;
				else
					pBuffer->up->right = pChildBuffer;
			}

			// �� ����
			deletedNodeColor = pBuffer->color;
		}
		// �ڽ��� ����.
		else
		{
			pBuffer = pDeletedNode;

			// TEST ------------------------
			//pChildBuffer = pBuffer->right;
			pChildBuffer->up = pBuffer->up;
			// TEST ------------------------

			if (pBuffer->up == pNullNode)
				pRoot = pNullNode;//pChildBuffer;
			else
			{
				if (pBuffer->up->left == pBuffer)
					pBuffer->up->left = pNullNode;
				else
					pBuffer->up->right = pNullNode;
			}

			// �� ����
			deletedNodeColor = pBuffer->color;
		}

		if (deletedNodeColor == BLACK)
		{
			if (pChildBuffer->color == BLACK)
				_ChangeForDelete(pChildBuffer);
			else
				pChildBuffer->color = BLACK;
		}

		pRoot->color = BLACK;

		// TEST ------------------------
		pNullNode->up = nullptr;
		// TEST ------------------------

		//delete pBuffer;
		delete pDeletedNode;
	};


	/*
		_ChangeForDelete(rbTreeNode<DATA, KEY_TYPE>* pInNode);
			- Delete �Լ� ���ο��� ���Ǹ�, ��带 Delete �� �Ŀ���, Red-Black Tree�� Ư¡�� �����ϱ� ���� �˻� ��, �ʿ� �� ó���� ���ִ� �Լ��Դϴ�.

		���� : Delete�� ����� NextNode( Successor )�� ChildNode (dir - Right)
		��� : void
		
		#0. ���� �̷��� ��Ű ���, ����-�� Ʈ���� Ȯ���� �ּ���! https://ko.wikipedia.org/wiki/%EB%A0%88%EB%93%9C-%EB%B8%94%EB%9E%99_%ED%8A%B8%EB%A6%AC
	*/
	template <typename DATA, typename KEY_TYPE>
	void rbTree<DATA, KEY_TYPE>::_ChangeForDelete(_Node* pInNode)
	{
	LIKE_RECURSION:

		// [Delete_Case_1]
		if (pInNode->up == pNullNode)
			return;

		// [Delete_Case_2]
		rbTreeNode<DATA, KEY_TYPE>* pSiblingNode = _GetSiblingNode(pInNode);

		if (pSiblingNode->color == RED)
		{
			pInNode->up->color = RED;
			pSiblingNode->color = BLACK;

			// �� ��尡, �θ��� ���� �ڽ��� ���
			if (pInNode == pInNode->up->left)
				_LeftRotate(pInNode->up);
			// �� ��尡, �θ��� ������ �ڽ��� ���
			else
				_RightRotate(pInNode->up);
		}

		// [Delete_Case_3]

		pSiblingNode = _GetSiblingNode(pInNode);

		if (pInNode->up->color == BLACK && pSiblingNode->color == BLACK && pSiblingNode->left->color == BLACK && pSiblingNode->right->color == BLACK)
		{
			pSiblingNode->color = RED;
			pInNode = pInNode->up;
			goto LIKE_RECURSION;
			// [Delete_Case_1] pInNode->up;
		}

		// [Delete_case_4]

		else if (pInNode->up->color == RED && pSiblingNode->color == BLACK && pSiblingNode->left->color == BLACK && pSiblingNode->right->color == BLACK)
		{
			pSiblingNode->color = RED;
			pInNode->up->color = BLACK;
		}

		else {
			// [Delete_case_5]

			if (pSiblingNode->color == BLACK)
			{
				if (pInNode == pInNode->up->left && pSiblingNode->right->color == BLACK && pSiblingNode->left->color == RED)
				{
					pSiblingNode->color = RED;
					pSiblingNode->left->color = BLACK;
					_RightRotate(pSiblingNode);
				}
				else if (pInNode == pInNode->up->right && pSiblingNode->left->color == BLACK && pSiblingNode->right->color == RED)
				{
					pSiblingNode->color = RED;
					pSiblingNode->right->color = BLACK;
					_LeftRotate(pSiblingNode);
				}
			}

			// [Delete_case_6]
			pSiblingNode = _GetSiblingNode(pInNode);

			pSiblingNode->color = pInNode->up->color;
			pInNode->up->color = BLACK;

			if (pInNode == pInNode->up->left)
			{
				pSiblingNode->right->color = BLACK;
				_LeftRotate(pInNode->up);
			}
			else {
				pSiblingNode->left->color = BLACK;
				_RightRotate(pInNode->up);
			}
		}
	};


	/*
		DeleteWithSearch(const DATA& InKey);
			- Ű�� ���ڷ� �޾�, �ش� Ű�� �ش��ϴ� ��带 ã��, �� ��带 �����մϴ�, �ش��ϴ� Ű ���� ���� ��尡 ���� ��, �������� �ʽ��ϴ�.

		���� : �����Ϸ��� ����� Ű��.
		��� : bool�� - ��� ���� ���� ( == �ش� Ű�� ���� ����� ���� ���� )
	
		#0. Ptr�� ����ϴ� ���� �Լ� (Delete) ���� �翬�� ���̽��ϴ�. (Search �߰�)

		!0. ���ο��� ã�� Node�� ���� �޸� ȸ��(delete) �� �Ͼ�ϴ�.

		!1. ����, �ܺο��� �ش� ��忡 �����͸� ���� ������ ���� ���, Dangling Pointer ���� ������ �� ���ɼ��� Ů�ϴ�.
	*/
	template <typename DATA, typename KEY_TYPE>
	bool rbTree<DATA, KEY_TYPE>::DeleteWithSearch(const KEY_TYPE& InKey)
	{
		bool retBoolBuffer;

		if (_Node* pDeletedNode = this->Search(InKey, retBoolBuffer)
			; retBoolBuffer)
		{
			Delete(pDeletedNode);

			return true;
		}
		else
		{
			return false;
		}
	}

	// ================================== Rotate

	/*
		_LeftRotate(rbTreeNode<DATA, KEY_TYPE>* pRetNode)
			- Ʈ���������� ���� ȸ���� �õ��մϴ�.

		���� : ȸ���� ������ �Ǵ� ����� ������
		��� : void
		
		#0. https://en.wikipedia.org/wiki/Tree_rotation
	*/
	template <typename DATA, typename KEY_TYPE>
	void rbTree<DATA, KEY_TYPE>::_LeftRotate(_Node* pRetNode)
	{
		_Node* pParentNode = pRetNode->up;
		_Node* pRightChildNode = pRetNode->right;

		// RetNode�� ���� Ʈ���� pRootNode�� �� ( ������ �ڽ��� ��Ʈ�� �� (LeftRotate) )
		if (pParentNode == pNullNode)
			pRoot = pRightChildNode;
		else
		{
			//���� ��尡 �θ� ����� ���� �ڽ� ����϶�,
			if (pRetNode == pParentNode->left)
				pParentNode->left = pRightChildNode;

			//���� ��尡 �θ� ����� ������ �ڽ� ����϶�,
			else
				pParentNode->right = pRightChildNode;
		}

		//���� Ret�� �θ����, Ret�� ������ �ڽ� ��带 �θ����� �ٲ��ְ�, Ret���� �ڽĳ���� �ڽ����� �����մϴ�.

		// �� �θ���� ���, �� �ڽ��� �θ���̴�.
		pRightChildNode->up = pRetNode->up;

		// �� �ڽ��� ���, �� �ڽ��� �ڽ� - ���ڴ�.
		pRetNode->right = pRightChildNode->left;

		// ���� �� �ڽ� - ������ �θ�� ����.
		pRightChildNode->left->up = pRetNode;

		// ...���� �� ���� �ڽ��� �ڽ��̴�.
		pRightChildNode->left = pRetNode;

		// �ᱹ �� �θ���� �� �� �ڽ��̴�.
		pRetNode->up = pRightChildNode;
	};


	/*
		_RightRotate(rbTreeNode<DATA, KEY_TYPE>* pRetNode)
			- Ʈ���������� ������ ȸ���� �õ��մϴ�.

		���� : ȸ���� ������ �Ǵ� ����� ������
		��� : void
		
		#0. https://en.wikipedia.org/wiki/Tree_rotation
	*/
	template <typename DATA, typename KEY_TYPE>
	void rbTree<DATA, KEY_TYPE>::_RightRotate(_Node* pRetNode)
	{
		_Node* pParentNode = pRetNode->up;
		_Node* pLeftChildNode = pRetNode->left;

		// �ּ� _LeftRotate �ϰ� �����մϴ�..�� ���� �ʹ� �������...

		if (pParentNode == pNullNode)
			pRoot = pLeftChildNode;
		else
		{
			if (pRetNode == pRetNode->up->left)
				pRetNode->up->left = pLeftChildNode;
			else
				pParentNode->right = pLeftChildNode;
		}

		pLeftChildNode->up = pRetNode->up;

		pRetNode->left = pLeftChildNode->right;
		pLeftChildNode->right->up = pRetNode;

		pLeftChildNode->right = pRetNode;
		pRetNode->up = pLeftChildNode;
	};


	// ================================== GetNode Function

	/*
		_GetPrevNode(rbTreeNode<DATA, KEY_TYPE>* InNode);
			- Predecessor�� ���ϴ� �Լ�, ������ �ʽ��ϴ�. _GetNextNode�� ���˴ϴ�. �ش� �Լ� ������ Ȯ�����ּ���.

		���� : Delete�Ǿ�, PrevNode�� ���ؾ��ϴ� ����� ������
		��� : Predecessor Node's Pointer
	*/

	template <typename DATA, typename KEY_TYPE>
	rbTreeNode<DATA, KEY_TYPE>*	rbTree<DATA, KEY_TYPE>::_GetPrevNode(_Node* const pInNode)
	{
		_Node* pRetNode = pInNode;

		// ������ NullNode�� �ƴ� ���, 
		if (pRetNode->left != pNullNode) {

			// �������� �����͸� �� �� �̵��ϰ� (���� ����Ʈ���� �����ϰ�)
			pRetNode = pRetNode->left;

			// �ش� ����Ʈ������ ���� ū �� (���� Right�� �ִ� ���)�� ã��,
			while (pRetNode->right != pNullNode)
			{
				pRetNode = pRetNode->right;
			}

			// �ش� ��带 �����մϴ�.
			return pRetNode;
		}
	};

	/*
		_GetNextNode(rbTreeNode<DATA, KEY_TYPE>* InNode);
			- ����( ���� �����Դϴ�.) : https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/

		���� �����帮��, ���� ��� ������ GetNextNode��� �Լ����� ������
		���õǾ� ���� ���Ǵ� ��Ī�� Predecessor, Successor�̸� ����, �ش� ����� ���� ����Ʈ���� �ִ밪 (Predecessor), �ش� ����� ���� ����Ʈ���� �ּҰ� (Successor) Ȥ�� ��带 ���ϴ� �ܾ��Դϴ�.

		�̴� ����Ʈ����� �ڷᱸ�� Ư���� ������ ���� �ǹ̸� ���մϴ�.
		�����Ǵ� ��尡 �� ���� pNullNode�� �ƴ� �ڽ��� ���� ���, �ش� ����� �ڸ��� � ��尡 �;��ϴ� ���� ���ϴ� ���̸�,
		�� �ڸ��� �� �� �ִ� ���� Predecessor �Ǵ� Successor�� �ֽ��ϴ�.

		����� �Ϲ����� ����Ʈ������ �����ϴ� ��尡 �ڽ��� ���� ���, ��� �����ϸ� �ǰ�,
		�����ϴ� ��尡 1���� �ڽ��� ���� ���� ���, �ش� �ڽ��� �� �ڸ��� ��ġ��Ű�� �˴ϴ�.
	*/
	template <typename DATA, typename KEY_TYPE>
	rbTreeNode<DATA, KEY_TYPE>*	rbTree<DATA, KEY_TYPE>::_GetNextNode(_Node* const InNode)
	{
		_Node* RetNode = InNode;

		// ������ NullNode�� �ƴ� ���, 
		if (RetNode->right != pNullNode) {

			// �������� �����͸� �� �� �̵��ϰ� (���� ����Ʈ���� �����ϰ�)
			RetNode = RetNode->right;

			// �ش� ����Ʈ������ ���� ���� �� (���� Left�� �ִ� ���)�� ã��,
			while (RetNode->left != pNullNode)
			{
				RetNode = RetNode->left;
			}

			// �ش� ��带 �����մϴ�.
			return RetNode;
		}
	};


	/*
		_GetSiblingNode(rbTreeNode<DATA, KEY_TYPE>* pInNode);
			- pInNode�� ���� ����� �����͸� ���ϴ� �Լ��Դϴ�.

		���� : ����� ������
		��� : ���� ����� ������
	*/
	template <typename DATA, typename KEY_TYPE>
	rbTreeNode<DATA, KEY_TYPE>*	rbTree<DATA, KEY_TYPE>::_GetSiblingNode(_Node* const pInNode)
	{
		_Node* pBufferNode = pInNode->up;

		if (pBufferNode->left == pInNode)
		{
			return pBufferNode->right;
		}
		else /*if (pBufferNode->right == pInNode) */
		{
			return pBufferNode->left;
		}
		//else
		//{
		//	std::cout << "Error - ���� ��带 ��ȯ�ϴ� �Լ����� ���ܰ� �߻��߽��ϴ�. \n";
		//}
	}


	/*
		_GetUncleNode(rbTreeNode<DATA, KEY_TYPE>* pInNode);
			- pInNode�� Uncle ����� �����͸� ���ϴ� �Լ��Դϴ�.

		���� : ����� ������
		��� : ���� ����� ������
	*/
	template <typename DATA, typename KEY_TYPE>
	rbTreeNode<DATA, KEY_TYPE>*	rbTree<DATA, KEY_TYPE>::_GetUncleNode(_Node* const pInNode)
	{
		_Node* pGrandParentNode = pInNode->up->up;

		if (pInNode->up == pGrandParentNode->left)
			return pGrandParentNode->right;
		else /*if (pInNode->up == pGrandParentNode->right) */
			return pGrandParentNode->left;
		//else
		//{
		//		std::cout << "Error - Uncle ��带 ��ȯ�ϴ� �Լ����� ���ܰ� �߻��߽��ϴ�. \n";
		//}
	}


	// ================================== Debug Function

	//Debug Function

	/*
		!0. ����Լ��� Ȱ���ϰ� �ֽ��ϴ�. Ʈ�� ���̰� ���� ���, ���� �����÷ο찡 �߻��� �� �ֽ��ϴ�.
		(����� �뵵�θ� ����ϴ� ���� ��õ�帳�ϴ�.)
	*/

	template <typename DATA, typename KEY_TYPE>
	void rbTree<DATA, KEY_TYPE>::PrintTree()
	{
		_Node* pNodeBuffer = pRoot;

		if (pRoot != pNullNode)
		{
			std::cout << "pRootNode's Key : " << pRoot->GetKey() << "\n";
			std::cout << "Node - Key   Color   Up     Left     Right \n";
			_PrintNodes(pRoot);
		}
		else
			cout << "Tree pRoot is pNullNode (VOID-TREE) \n";
	}

	template <typename DATA, typename KEY_TYPE>
	void rbTree<DATA, KEY_TYPE>::_PrintNodes(_Node* pNodeBuffer)
	{
		if (pNodeBuffer->left != pNullNode)
			_PrintNodes(pNodeBuffer->left);

		pNodeBuffer->PrintNodeInfo(pNullNode);

		if (pNodeBuffer->right != pNullNode)
			_PrintNodes(pNodeBuffer->right);
	}

#pragma endregion

#pragma region [ Test Func ]
#ifdef DEBUG_TEST_FUNC
	class TestKey
	{
		int keyValue;
	public:

		TestKey(int InValue) : keyValue(InValue) {};
		TestKey() = default;	// for rbtreenode demo
		~TestKey() = default;
	public:
		_NODISCARD INLINE bool operator<(const TestKey& other) const noexcept { return keyValue < other.keyValue ? true : false; };
		_NODISCARD INLINE bool operator==(const TestKey& other) const noexcept { return keyValue == other.keyValue ? true : false; };
		_NODISCARD INLINE friend std::ostream& operator<<(std::ostream& os, const TestKey& my) { os << my.keyValue; return os; };
	};

	class TestData
	{
		TestKey key;
		//others...

	public:
		TestData(const TestKey& InKey) : key(InKey) {};
		TestData() = default; // for rbtreenode demo
		~TestData() = default;
	public:
		_NODISCARD INLINE TestKey GetKey() const noexcept { return key; };
	};

	void TestFunc()
	{
		rbTree<TestData, TestKey> testCont;
		testCont.Insert([]()-> TestData { TestData data([]()->TestKey {TestKey key(5); return key; }()); return data; }());
		testCont.Insert([]()-> TestData { TestData data([]()->TestKey {TestKey key(3); return key; }()); return data; }());
		testCont.Insert([]()-> TestData { TestData data([]()->TestKey {TestKey key(1); return key; }()); return data; }());
		testCont.Insert([]()-> TestData { TestData data([]()->TestKey {TestKey key(4); return key; }()); return data; }());
		testCont.Insert([]()-> TestData { TestData data([]()->TestKey {TestKey key(2); return key; }()); return data; }());

		testCont.PrintTree();
	}
#endif
#pragma endregion
}