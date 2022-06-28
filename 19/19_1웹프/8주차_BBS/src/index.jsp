<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="bbsManage.*" %>
<%@ page import="java.util.ArrayList" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<link rel="stylesheet" href="./main.css">
</head>
<body>
<h1 style="text-align: center;">Modern BBS</h1>
<button id="addBtn" onclick="location.href='./addBoard.html'">글 작성</button>
<div class="content">
    <div class="page"> 
        <!--        page start         -->
  	<% 
  		ArrayList<ArticleEntity> articleList = null;
  		boardDAO bdao = new boardDAO();
  		articleList = bdao.getArticleList(0);
  		
  		for(ArticleEntity article : articleList){
  	%>
            <br><br>
            <div class="card">
                <div class="tag">
                    <span class="name"><%=article.getName() %></span> : <span class="title"><a href="./article.jsp?anum=<%= article.getNum()%>"><%=article.getTitle() %></a></span>
                </div>
                <div class="tagb"><%= article.getDate() %></div>
                <hr>
                <div class="tagFoot">
                    <%= article.getContent()%>
                </div>
            </div>
            <% } %>    
            
            <!--        page end            -->
        </div>
    </div>
    </body>
    </html>