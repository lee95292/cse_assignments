<%@page import="java.io.*"%>
<%@page import="java.util.Date" %>
<%@page import="java.util.*" %>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
	<%!

		Date date;
		int time;
		String filePath;
		String fileName;
		PrintWriter pw;
		static Integer id=0;
		
		Enumeration<String> result;
	%>
	
	<%
		request.setCharacterEncoding("UTF-8");
		date = new Date();
		time = (int)date.getTime();			
	
		result=request.getParameterNames();
		
		if(!result.hasMoreElements()){
			out.println("<script type='text/javascript'>");
			out.println("alert('abnormal access')");
			out.print("location.href='./index.html';</script>");
		}else{
			out.print("\n\n :: "+result.toString());
		}
		//out.println(name+gender+major);
	
		id++;
		
		%>
</head>
<body>		
		<% 
		try{
			fileName=""+time;
			filePath= application.getRealPath("/")+"__"+id+"__"+fileName+".txt";
			
			out.println(filePath);
			
			pw= new PrintWriter(new FileWriter(filePath),true);
			System.out.println(filePath+"opened");
			pw.print(id);
			while(result.hasMoreElements()){
				String key = result.nextElement();
				String value= request.getParameter(key);
				out.println(key+": "+value+"\n");
				pw.println("__"+key+":"+value+" ");				
			}
			pw.close();
		}catch(Exception e){
			e.printStackTrace();
		}
		
		response.sendRedirect("./Success.html");
	%>
</body>
</html>