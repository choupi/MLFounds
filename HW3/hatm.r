m <- rbind(c(1,2),c(3,4),c(5,6))
hm <- m %*% solve(t(m)%*%m) %*% t(m)
eigen(hm)

