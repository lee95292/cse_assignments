<%@page import="gradeManage.GradeBean"%>
<%@page import="gradeManage.GradeDAO"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="com.oreilly.servlet.multipart.DefaultFileRenamePolicy" %>
<%@ page import="com.oreilly.servlet.MultipartRequest" %>
<%@ page import="java.io.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>

<%
	String saveDir= application.getRealPath("/");
	int maxSize = 1024*1024*10;
	String encType="UTF-8";
	
	GradeBean gbean=null;
	
	MultipartRequest mpRequest = new MultipartRequest(request,saveDir,maxSize,encType,new DefaultFileRenamePolicy());
	
	File grade = mpRequest.getFile("gradeFile");
	BufferedReader bf;			// .. = null 하는것과 안하는 것의 차이는 무엇일까?
	String line=null;
	String[] args;
	try{
		
		GradeDAO gdao = new GradeDAO();
		bf = new BufferedReader(new FileReader(grade));
		gdao.updateTable();
		while((line=bf.readLine())!=null){
			gbean = new GradeBean();
			gbean.setName(session.getAttribute("id").toString());
	
			args = line.split(",");
			
			if(args.length!=4)continue;
			gbean.setName(gbean.getName()+"_"+args[0]);
			gbean.setLab1(Integer.parseInt(args[1]));
			gbean.setLab2(Integer.parseInt(args[2]));
			gbean.setMidterm(Integer.parseInt(args[3]));			
			gdao.addGrade(gbean);
		}
		bf.close();
	}catch(FileNotFoundException e){
		e.printStackTrace();
	}catch(Exception e){
		e.printStackTrace();
	}
	
	
%>
</body>
</html>