package models

type ListNode struct {
	Data Grades
	Next *ListNode
}

type Grades struct {
	Grade float32
	Point int
}
