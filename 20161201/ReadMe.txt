組員：
1041621 蘇建文
1041649 蒲民軒
1041656 張楷翊

程式碼介紹：
Functions:
    operateOrNot: 僅在第 99 行使用到，用來比較優先度，看是要存進 Stack 還是做運算。
    operation: 做加減乘除、次方的運算，其中會檢驗運算元的 Stack 有沒有兩個，如果少於兩個，不能運算。
    main: 讀入輸入的東西，並且拆解。在最後 (可能成功運算，可能失敗) 時會 pop 全部的東西，在下一次運算時才不會出錯。
Global Variables:
    error: 
        在任何地方出現錯誤都會變成 true。
        1) operateOrNot 中遇到不認識的符號
        2) operation 中沒有兩個運算元
        3) 遇到 ')' 但是 Stack 又是空的 
    Stacks:
        operators: 運算子
        operands: 運算元

詳細訊息在 code 中的註解都有介紹。